fn enigmatic(mut s: String) -> String {
    s.chars().rev().collect()
}

fn main() {
    let encrypted = "STF";
    let decrypted = enigmatic(encrypted.to_string());
    println!("{}", decrypted);
}