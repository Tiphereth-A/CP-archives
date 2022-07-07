use std::io;
fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let mut s = input.trim().split(' ');
    let a: i32 = s.next().unwrap().parse().unwrap();
    let b: i32 = s.next().unwrap().parse().unwrap();
    println!("{}", a + b);
}
