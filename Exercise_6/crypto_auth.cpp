#include <boost/asio.hpp>
#include <iostream>
#include <openssl/evp.h>

using namespace std;
using namespace boost::asio::ip;

const int DIGEST_SIZE = 128;
const int NUM_ITERATIONS = 2048;
const unsigned char SERVER_SALT[] = "v9m4(%\\#32pfm§=#()mc9n9ec+e98^'*d2q3fn";
const unsigned char CLIENT_SALT[] = "pwoeijpzsdfmoiw45wh457jmw03r49ey923rf92";
const char AUTH_SUCCESS = 56;
const char AUTH_FAILURE = 47;

void create_password(const char *password, unsigned char *hash_out)
{
  char client_hash[DIGEST_SIZE + 1];

  memset(client_hash, 0, DIGEST_SIZE + 1);
  memset(hash_out, 0, DIGEST_SIZE + 1);

  int err = PKCS5_PBKDF2_HMAC_SHA1(
      password,                      // password
      strlen(password),              // password length
      CLIENT_SALT,                   // salt
      sizeof(CLIENT_SALT) - 1,       // salt length
      NUM_ITERATIONS,                // number of iterations
      DIGEST_SIZE,                   // derived key length
      (unsigned char *)(client_hash) // output hash buffer
  );

  err = PKCS5_PBKDF2_HMAC_SHA1(
      client_hash,             // password
      DIGEST_SIZE,             // password length
      SERVER_SALT,             // salt
      sizeof(SERVER_SALT) - 1, // salt length
      NUM_ITERATIONS,          // number of iterations
      DIGEST_SIZE,             // derived key length
      hash_out                 // output hash buffer
  );

  // Cleanup client hash, to not leak any secrets.
  memset(client_hash, 0, DIGEST_SIZE + 1);
}

using boost::asio::ip::tcp;

class auth_server
{
public:
  auth_server(boost::asio::io_context &io_context, short port, const char *password) : io_context(io_context), acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
  {
    create_password(password, auth_hash);
    start_accept();
  }

  ~auth_server()
  {
    acceptor_.close();
  }

private:
  unsigned char auth_hash[DIGEST_SIZE + 1];
  tcp::acceptor acceptor_;
  boost::asio::io_context &io_context;

  void start_accept()
  {
    std::shared_ptr<tcp::socket> socket = std::make_shared<tcp::socket>(io_context);
    // Asynchronously accept a new connection
    acceptor_.async_accept(*socket, [this, socket](const boost::system::error_code &error)
                           {
      if (!error)
      {
        // std::cout << "Client connected!" << std::endl;
        handle_client(socket);
      }

      // Accept another connection
      start_accept(); });
  }

  void handle_client(std::shared_ptr<tcp::socket> socket)
  {
    auto buffer = std::make_shared<std::array<char, 128>>();

    // Asynchronously read data from the client
    socket->async_read_some(boost::asio::buffer(*buffer), [this, socket, buffer](const boost::system::error_code &error, std::size_t bytes_transferred)
                            {
      if (!error && bytes_transferred != 1) {
      
      // std::cout << "Received: " << std::string(buffer->data(), bytes_transferred) << std::endl;
      unsigned char hash[DIGEST_SIZE + 1];

      int err = PKCS5_PBKDF2_HMAC_SHA1(
        buffer->data(),          // password
        bytes_transferred,       // password length
        SERVER_SALT,             // salt
        sizeof(SERVER_SALT) - 1, // salt length
        NUM_ITERATIONS,          // number of iterations
        DIGEST_SIZE,             // derived key length
        hash                     // output hash buffer
      );

      hash[DIGEST_SIZE] = '\0';
      const int correct_password = !memcmp(hash, auth_hash, DIGEST_SIZE);
      buffer->data()[0] = correct_password ? AUTH_SUCCESS : AUTH_FAILURE;

      // Echo the message back to the client
      boost::asio::async_write(*socket, boost::asio::buffer(*buffer, 1), [socket, correct_password](const boost::system::error_code &error, std::size_t /*bytes_transferred*/)
      {
        if (error)
          return;
      });

      // Keep reading data from the client
      handle_client(socket); } });
  }
};

class auth_client
{
private:
  tcp::socket socket;
  tcp::resolver::results_type endpoints;

public:
  auth_client(boost::asio::io_context &io_context, std::string destination, std::string port) : socket(io_context), endpoints(tcp::resolver(io_context).resolve(destination, port))
  {
    boost::asio::connect(socket, endpoints);
  }

  ~auth_client()
  {
    socket.shutdown(boost::asio::socket_base::shutdown_type::shutdown_both);
    socket.close();
  }

  int try_password(const std::string &password) { return try_password(password.c_str()); }

  int try_password(const char *password)
  {
    unsigned char hash[DIGEST_SIZE + 1];
    memset(hash, 0, sizeof(hash));
    hash[DIGEST_SIZE] = '\0';

    int err = PKCS5_PBKDF2_HMAC_SHA1(
        password,                // password
        strlen(password),        // password length
        CLIENT_SALT,             // salt
        sizeof(CLIENT_SALT) - 1, // salt length
        NUM_ITERATIONS,          // number of iterations
        DIGEST_SIZE,             // derived key length
        hash                     // output hash buffer
    );
    boost::asio::write(socket, boost::asio::buffer(hash));

    char response[1];
    size_t response_length = socket.read_some(boost::asio::buffer(response));

    return response[0] == AUTH_SUCCESS;
  }
};

int main()
{
  boost::asio::io_context io_context_server;
  boost::asio::io_context io_context_client;

  const char password[] = "TestPassword";
  auth_server server(io_context_server, 8080, password);
  auth_client client(io_context_client, "localhost", "8080");

  std::thread server_thread([&io_context_server]()
                            { io_context_server.run(); });

  std::thread client_thread([&io_context_client]()
                            { io_context_client.run(); });

  int success = client.try_password(password);

  printf("Authentication %s\n", success ? "SUCCESS" : "FAILED");

  io_context_client.stop();
  io_context_server.stop();

  client_thread.join();
  server_thread.join();

  return 0;
}
