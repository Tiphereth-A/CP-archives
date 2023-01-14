import java.util.Scanner
fun main() {
    val read = Scanner(System.`in`)
    var n: Long = read.nextInt().toLong()
    var s = hashSetOf(n)
    var str = ""
    while (true) {
        str = (n + 1).toString().reversed().toLong().toString().reversed()
        if (str == "") str = "0"
        n = str.toLong()
        if (s.indexOf(n) > 0) break
        else s.add(n)
    }
    println(s.count())
}
