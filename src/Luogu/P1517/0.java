import java.math.*;
import java.util.Scanner;
public class Main {
  public static void main(String[] args) {
    Scanner read = new Scanner(System.in);
    BigDecimal a;
    while (read.hasNext()) {
      a = read.nextBigDecimal();
      int b = read.nextInt();
      String S = a.pow(b).toPlainString();
      int l = 0, ed = S.length();
      for (int i = 0; i < S.length(); ++i) {
        l = i;
        if (S.charAt(i) >= '1' && S.charAt(i) <= '9' || S.charAt(i) == '.')
          break;
      }
      for (int i = S.length() - 1; i >= 0; --i) {
        ed = i;
        if (S.charAt(i) >= '1' && S.charAt(i) <= '9') break;
        if (S.charAt(i) == '.') {
          --ed;
          break;
        }
      }
      String ans = S.substring(l, ed + 1);
      System.out.println(ans);
    }
  }
}
