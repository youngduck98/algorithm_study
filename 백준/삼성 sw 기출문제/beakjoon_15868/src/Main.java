import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class Camera{
    static final int[] dirR = {0, -1, 0, 1};
    static final int[] dirC = {1, 0, -1, 0};
    public static boolean validPosition(char[][] map, int r, int c){
        return r<map.length && r>= 0 && c<map[0].length && c>=0 && map[r][c] != '6';
    }

    public static void coloringCamera(char[][] map, int dir, int r, int c, char type){
        switch (type){
            case '1': coloring(map, dir, r, c); break;
            case '2': coloring2(map, dir, r, c); break;
            case '3': coloring3(map, dir, r, c); break;
            case '4': coloring4(map, dir, r, c); break;
            case '5': coloring5(map, dir, r, c); break;
        }
    }
    public static void coloring(char[][] map, int dir, int r, int c){
        for(;validPosition(map, r, c);r+=dirR[dir], c+=dirC[dir]){
            if(map[r][c] == '0') {
                map[r][c] = '#';
            }
        }
    }

    public static void coloring2(char[][] map, int dir, int r, int c) {
        coloring(map, dir, r, c);
        coloring(map, (dir+2)%4, r, c);
    }

    public static void coloring3(char[][] map, int dir, int r, int c) {
        coloring(map, dir, r, c);
        coloring(map, (dir+1)%4, r, c);
    }

    public static void coloring4(char[][] map, int dir, int r, int c) {
        coloring(map, dir, r, c);
        coloring(map, (dir+1)%4, r, c);
        coloring(map, (dir+2)%4, r, c);
    }

    public static void coloring5(char[][] map, int dir, int r, int c) {
        coloring(map, dir, r, c);
        coloring(map, (dir+1)%4, r, c);
        coloring(map, (dir+2)%4, r, c);
        coloring(map, (dir+3)%4, r, c);
    }
}

class Pos{
    int r;
    int c;
    public Pos(int r, int c){
        this.r = r;
        this.c = c;
    }
}

public class Main {
    char[][] originMap;
    List<Pos> cameraPosList = new ArrayList<>();
    int nowMin = Integer.MAX_VALUE;

    public char[][] createCopiedMap(char[][] origin){
        char[][] copiedMap = new char[origin.length][origin[0].length];
        for(int i=0;i<origin.length;i++){
            copiedMap[i] = Arrays.copyOf(origin[i], origin[i].length);
        }
        return copiedMap;
    }

    public void initialize() throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] inputs = br.readLine().split(" ");
        int maxR = Integer.parseInt(inputs[0]);
        int maxC = Integer.parseInt(inputs[1]);
        originMap = new char[maxR][maxC];

        for(int r=0;r<maxR;r++){
            inputs = br.readLine().split(" ");
            for(int c=0;c<maxC;c++){
                originMap[r][c] = inputs[c].charAt(0);
                if(originMap[r][c] >= '1' && originMap[r][c] <= '5'){
                    cameraPosList.add(new Pos(r, c));
                }
            }
        }
    }

    public int count(char[][] map){
        int ret=0;
        for (char[] chars : map) {
            for (int c = 0; c < map[0].length; c++) {
                if (chars[c] == '0')
                    ret++;
            }
        }
        return ret;
    }

    public void DFS(int index, char[][] map){
        if(index == cameraPosList.size()){
            int now = count(map);
            if(nowMin > now)
                nowMin = now;
            return;
        }
        int r = cameraPosList.get(index).r;
        int c = cameraPosList.get(index).c;
        for(int i=0;i<4;i++){
            if(map[r][c] == '5' && i != 0)
                continue;
            if(map[r][c] == '2' && i > 2)
                continue;
            char[][] copiedMap = createCopiedMap(map);
            Camera.coloringCamera(copiedMap, i, r, c, copiedMap[r][c]);
            DFS(index+1, copiedMap);
        }
    }

    public void Demo() throws IOException{
        initialize();
        DFS(0, originMap);
        System.out.println(nowMin);
    }

    public static void main(String[] args) throws IOException{
        Main main = new Main();
        main.Demo();
    }
}