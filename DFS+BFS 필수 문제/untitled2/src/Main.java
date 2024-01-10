import javax.imageio.IIOException;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
    int[][] map;
    int length;

    public Main(int[][] map, int length){
        this.map = map;
        this.length = length;
    }
    public boolean roadH(int index){
        //2칸보다 차이 많이 나는 경우
        //1칸 위에 있는 경우
        //1칸 아래에 있는 경우
        boolean[] visited = new boolean[map[index].length];//전 다리 놓는데 쓰임
        int lastIndex = -1; //앞에 다리 놓는데 쓰임 - 여기 까지 다리 놓아짐

        for(int i=0;i<map[index].length-1;i++){
            if(i < lastIndex && map[index][i] != map[index][i+1])
                return false;
            if(map[index][i] == map[index][i+1])
                continue;
            if(map[index][i] - 1 == map[index][i+1]){
                lastIndex = i + length;
                if(lastIndex >= map[index].length)
                    return false;
                continue;
            }
            if(map[index][i] + 1 == map[index][i+1]){
                if(i - length + 1 <= lastIndex)
                    return false;
                lastIndex = i;
                continue;
            }
            return false;
        }
        return true;
    }
    public boolean roadV(int index){
        boolean[] visited = new boolean[map.length];//전 다리 놓는데 쓰임
        int lastIndex = -1; //앞에 다리 놓는데 쓰임 - 여기 까지 다리 놓아짐

        for(int i=0;i<map.length-1;i++){
            if(i < lastIndex && map[i][index] != map[i+1][index])
                return false;
            if(map[i][index] == map[i+1][index])
                continue;
            if(map[i][index] - 1 == map[i+1][index]){
                lastIndex = i + length;
                if(lastIndex >= map.length)
                    return false;
                continue;
            }
            if(map[i][index] + 1 == map[i+1][index]){
                if(i - length + 1 <= lastIndex)
                    return false;
                lastIndex = i;
                continue;
            }
            return false;
        }
        return true;
    }
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] input = br.readLine().split(" ");
        int size = Integer.parseInt(input[0]);
        int length = Integer.parseInt(input[1]);
        int[][] map = new int[size][size];
        for(int i=0;i<size;i++){
            input = br.readLine().split(" ");
            for(int c=0;c<size;c++){
                map[i][c] = Integer.parseInt(input[c]);
            }
        }
        Main main = new Main(map, length);
        int answer = 0;
        for(int i=0;i<size;i++){
            if(main.roadH(i)) {
                answer++;
            }
            if(main.roadV(i)) {
                answer++;
            }
        }
        System.out.println(answer);
    }
}