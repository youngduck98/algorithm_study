import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.Map;

public class Main {

    public static long calN(long n, long exp){
        return (n / (long)Math.pow(2.0, (double) exp)+1)/2;
    }

    public static void main(String[] args) throws IOException {
        //짝수 약수 개수 = k * 홀수 약수 개수
        //dp?
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int numOfData = Integer.parseInt(br.readLine());
        for(int i=0;i<numOfData;i++){
            String[] inputs = br.readLine().split(" ");
            long N = Long.parseLong(inputs[0]);
            long k = Long.parseLong(inputs[1]);
            if(N < k) {
                System.out.println(0);
                break;
            }
            System.out.println(calN(N, k));
        }
    }
}