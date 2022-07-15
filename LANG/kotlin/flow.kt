import java.io.*
import kotlin.system.measureTimeMillis

class Graph(val n: Int, val s: Int, val t: Int) {
    inner class Edge(val i: Int, var f: Long, var c: Long, val to: Int, var reverse: Edge?)
    val g = Array(n) {ArrayList<Edge>()}
    fun add(i: Int, a: Int, b: Int, c1: Long, c2: Long = 0L) {
        g[a].add(Edge(i, 0L, c1, b, null))
        g[b].add(Edge(-1, 0L, c2, a, g[a].last()))
        g[a].last().reverse = g[b].last()
    }

    val pos = IntArray(n) {0}
    val h = IntArray(n) {0}
    val gap = IntArray(2 * n + 1) {0}

    fun dfs(v: Int, flow: Long): Long {
        if (v == t)
            return flow
        var sum = 0L
        while (pos[v] < g[v].size) {
            val e = g[v][pos[v]]
            if (h[v] == h[e.to] + 1 && e.c - e.f > 0) {
                val df = dfs(e.to, minOf(e.c - e.f, flow - sum))
                sum += df
                e.f += df
                e.reverse!!.f -= df
                if (sum == flow)
                    return flow
            }
            pos[v]++
        }
        if (--gap[h[v]] == 0)
            h[s] = n
        ++gap[++h[v]]
        pos[v] = 0
        return sum
    }

    fun maxFlow(): Long {
        var flow = 0L
        gap[0] = n
        while (h[s] < n)
            flow += dfs(s, Long.MAX_VALUE)
        return flow
    }
}

fun solve(input: BufferedReader, out: BufferedWriter) {
    val (n, m) = input.readLine().split(" ").map {it.toInt()}
    val g = Graph(n, 0, n - 1)
    for (i in 0 until m) {
        val (a, b, c) = input.readLine().split(" ").map {it.toInt()}
        g.add(i, a - 1, b - 1, c.toLong())
    }
    val flow = g.maxFlow()
    out.write("$flow\n")
    val ans = LongArray(m) {-1}
    for (v in 0 until n) 
        for (e in g.g[v])
            if (e.i >= 0)
                 ans[e.i] = e.f;
    out.write(ans.joinToString("\n"))
}

fun main(args: Array<String>) {
    val i = System.`in`.bufferedReader()
    val o = System.`out`.bufferedWriter()
    System.err.println("time = ${measureTimeMillis {
        solve(i, o)
    }}ms")
    o.close()
}
