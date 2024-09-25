
fn string_to_html(source: &str) -> String {
    source.replace('&', "&amp;")
          .replace('<', "&lt;")
          .replace('>', "&gt;")
}

fn test_conversion(input: &str, expected: &str) -> bool {
    expected == string_to_html(input)
}

struct TestSample {
    input: String,
    expected: String,
}

fn main() {
    let samples: [TestSample; 3] = [
        TestSample{input: String::from("Buns&Bozinos"), expected: String::from("Buns&amp;Bozinos")},
        TestSample{input: String::from("1<2"), expected: String::from("1&lt;2")},
        TestSample{input: String::from("cake>vegetables"), expected: String::from("cake&gt;vegetables")}
        ];
    
    for (index, sample) in samples.iter().enumerate() {
        let equal: bool = test_conversion(&sample.input, &sample.expected);
        println!("Test {}: {} \"{}\" -> \"{}\"", index, if equal {"success"} else {"FAIL"}, sample.input, sample.expected);
    }
}