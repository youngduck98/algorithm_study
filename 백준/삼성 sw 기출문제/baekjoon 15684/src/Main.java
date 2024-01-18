import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
    int answer = 4;

    public boolean check(int[][] map){
        for(int i=0;i<map[0].length;i++){
            int k = i;
            for (int[] ins : map) {
                if (ins[k] == 1) {
                    k--;
                    continue;
                }
                if (ins[k] == 2)
                    k++;
            }
            if(k != i)
                return false;
        }
        return true;
    }

    public void DFS(int[][] map, int count, int index){
        if(answer <= count)
            return;
        if(check(map)){
            answer = count;
            return;
        }
        for(int r=0;r<map.length;r++){
            for(int c=0;c<map[0].length - 1;c++){
                if(r * map[0].length + c < index)
                    continue;
                if(map[r][c] == 0 && map[r][c+1] == 0){
                    map[r][c] = 2;
                    map[r][c+1] = 1;
                    DFS(map, count+1, r*map[0].length + c);
                    map[r][c] = map[r][c+1] = 0;
                }
            }
        }
    }
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] inputs = br.readLine().split(" ");
        int colMax = Integer.parseInt(inputs[0]);
        int nowBranch = Integer.parseInt(inputs[1]);
        int rowMax = Integer.parseInt(inputs[2]);
        int[][] map = new int[rowMax][colMax];

        for(int i=0;i<nowBranch;i++){
            inputs = br.readLine().split(" ");
            int row = Integer.parseInt(inputs[0]) - 1;
            int col = Integer.parseInt(inputs[1]) -1;
            if(map[row][col] == 0)
                map[row][col] = 2;
            if(map[row][col+1] == 0)
                map[row][col+1] = 1;
        }

        Main main = new Main();
        main.DFS(map, 0, -1);
        System.out.println(main.answer < 4 ? main.answer : -1);
    }
}
