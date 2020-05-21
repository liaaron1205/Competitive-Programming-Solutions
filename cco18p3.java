//CC0 2018 P3 - Fun Palace
import java.util.*;
import java.io.*;

public class Test {
    static int N, e, a[], b[], dp[][], max[][];
    public static void main(String[] args) throws IOException{
        N = readInt(); e = readInt();
        a = new int[N+5]; b = new int[N+5];
        dp = new int[N+5][20005]; max = new int[N+5][20005];
        for (int i = 2; i<=N; i++){
            a[i] = readInt(); b[i] = readInt();
        }
        for (int i = 0; i<=20000; i++){
            dp[1][i] = max[1][i] = i<e?i:0;
            if (i!=0) max[1][i] = Math.max(max[1][i], max[1][i-1]);
        }
        for (int i = 2; i<=N; i++){
            for (int j = 0; j<=20000; j++){
                if (j>=a[i]+b[i]) dp[i][j] = dp[i-1][j];
                else if (j>=b[i]) dp[i][j] = dp[i-1][j-b[i]] + b[i];
                else dp[i][j] = Math.max(max[i-1][a[i]-1]+j, dp[i-1][a[i]+j]);
                max[i][j] = dp[i][j];
                if (j!=0) max[i][j] = Math.max(max[i][j], max[i][j-1]);
            }
        }
        /*for (int i = 1; i<=N; i++){
            for (int j = 0; j<=25; j++){
                System.out.print(dp[i][j]+" ");
            }
            System.out.println();
        }*/
        System.out.println(max[N][20000]);    
    }  
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static StringTokenizer st;
    static String next() throws IOException {
            while (st == null || !st.hasMoreTokens())
                    st = new StringTokenizer(br.readLine().trim());
            return st.nextToken();
    }
    static long readLong() throws IOException {
            return Long.parseLong(next());
    }

    static float readFloat() throws IOException {
            return Float.parseFloat(next());
    }

    static boolean readBool() throws IOException {
            return Boolean.parseBoolean(next());
    }

    static short readShort() throws IOException {
            return Short.parseShort(next());
    }

    static byte readByte() throws IOException {
            return Byte.parseByte(next());
    }

    static int readInt() throws IOException {
            return Integer.parseInt(next());
    }

    static double readDouble() throws IOException {
            return Double.parseDouble(next());
    }

    static char readChar() throws IOException {
            return next().charAt(0);
    }

    static String readLine() throws IOException {
            return br.readLine().trim();
    }

    static PrintWriter pr = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

    static void print(Object o) {
            pr.print(o);
    }
}
