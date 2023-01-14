using System;
public class APlusB {
  private static void Main() {
    string[] input = Console.ReadLine().Split(' ');
    Console.WriteLine(int.Parse(input[0]) + int.Parse(input[1]));
  }
}
