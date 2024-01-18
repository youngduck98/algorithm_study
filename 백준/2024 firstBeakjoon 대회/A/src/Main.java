import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.PriorityQueue;

public class Main {
    public static void main(String[] args) throws IOException {
        int maxNum;
        int needNum;
        int count = 0;
        PriorityQueue<Integer> pq = new PriorityQueue<>();
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] inputs = br.readLine().split(" ");
        maxNum = Integer.parseInt(inputs[0]);
        needNum = Integer.parseInt(inputs[1]);
        for(int i=0;i<maxNum;i++){
            inputs = br.readLine().split(" ");
            int semiResult = Integer.parseInt(inputs[1]) - Integer.parseInt(inputs[0]);
            if(semiResult <= 0)
                count++;
            if(count >= needNum) {
                System.out.println(0);
                return;
            }
            if(semiResult > 0)
                pq.add(semiResult);
        }
        int k = 0;
        for(int i=0;i<needNum - count;i++){
            k = pq.remove();
        }
        System.out.println(k);
    }
}