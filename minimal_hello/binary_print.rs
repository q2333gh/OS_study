use std::fs::File;
use std::io::{BufReader, BufRead};

fn main() {
    // Open the file a.out in the current directory
    let file = File::open("a.out").expect("File not found");
    // Create a buffered reader to read the file
    let reader = BufReader::new(file);
    // Split the reader by the newline byte "\n"
    let lines = reader.split(b'\n');
    // Iterate over the lines in the reader
    for line in lines {
        // Get the line as a vector of u8
        let buffer = line.expect("Error reading line");
        // Print the buffer as hex format
        for byte in buffer {
            print!("{:02x}", byte);
        }
        // Print a new line
        println!();
    }
}
