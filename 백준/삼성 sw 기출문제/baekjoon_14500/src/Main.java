import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Main {
    int[][] map;
    boolean[][] visited;
    int nowMax = 0;
    int[] dirR = {0, -1, 0, 1};
    int[] dirC = {1, 0, -1, 0};

    public boolean vaildPosition(int r, int c){
        return (r >= 0 && r < map.length
                && c >= 0 && c < map[0].length);
    }

    public void DFS(int r, int c, int depth, int beforeValue, int banDir){
        if(!vaildPosition(r, c)) {
            return;
        }
        beforeValue += map[r][c];
        if(depth >= 4){
            if(nowMax < beforeValue)
                nowMax = beforeValue;
            return;
        }
        if(depth == 1){
            int value = 0;
            int count = 0;
            for(int ban=0;ban<4;ban++){
                value = beforeValue;
                count = 0;
                for(int i=0;i<4;i++){
                    if(i == ban)
                        continue;
                    if(vaildPosition(r + dirR[i], c+ dirC[i])) {
                        value += map[r + dirR[i]][c + dirC[i]];
                        count++;
                    }
                    if(count == 3 && nowMax < value){
                        nowMax = value;
                        }
                }
            }
        }

        for(int i=0;i<4;i++){
            if(i == banDir)
                continue;
            DFS(r+dirR[i], c+dirC[i], depth+1, beforeValue, (i+2)%4);
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] input = br.readLine().split(" ");
        int rowMax = Integer.parseInt(input[0]);
        int colMax = Integer.parseInt(input[1]);
        Main main = new Main();
        main.map = new int[rowMax][colMax];
        for(int r=0;r<rowMax;r++){
            input = br.readLine().split(" ");
            for(int c=0;c<colMax;c++){
                main.map[r][c] = Integer.parseInt(input[c]);
            }
        }
        for(int r=0;r<rowMax;r++) {
            for (int c = 0; c < colMax; c++) {
                main.DFS(r, c, 1, 0, -3);
            }
        }
        System.out.println(main.nowMax);
    }
}