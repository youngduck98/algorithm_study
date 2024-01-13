import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class Pos{
    int r;
    int c;
    public Pos(int r, int c){
        this.r = r;
        this.c = c;
    }
}

class WallSet{
    public WallSet(List<Pos> walls){
        this.walls = walls;
    }
    List<Pos> walls = new ArrayList<>();
}

public class Main {
    int rowMax;
    int colMax;
    int[][] originMap;
    int[][] copiedMap;
    List<WallSet> wallSetList = new ArrayList<>();
    List<Pos> canWall = new ArrayList<>();
    List<Pos> initialVirusPoses = new ArrayList<>();
    int numOfWall = 0;
    int numOfVirus = 0;
    int maxCount = 0;
    int[] dirR = {0, -1, 0, 1};
    int[] dirC = {1, 0, -1, 0};

    public void calCanWallAndWall(){
        for(int r=0;r<rowMax;r++){
            for(int c=0;c<colMax;c++){
                if(originMap[r][c] == 0)
                    canWall.add(new Pos(r, c));
                if(originMap[r][c] == 1)
                    numOfWall++;
                if(originMap[r][c] == 2)
                    initialVirusPoses.add(new Pos(r, c));
            }
        }
    }
    public void calWallSetList(int count, int beforeIndex, ArrayList<Pos> before){
        if(count == 3) {
            wallSetList.add(new WallSet(before));
            return;
        }
        for(int i=beforeIndex+1;i<canWall.size() - 2 + count;i++){
            ArrayList<Pos> copiedBefore = (ArrayList<Pos>) before.clone();
            copiedBefore.add(canWall.get(i));
            calWallSetList(count+1, i, copiedBefore);
        }
    }

    public void makeCopiedMap(WallSet wallSet){
        for(int i=0;i<rowMax;i++){
            copiedMap[i] = Arrays.copyOf(originMap[i], colMax);
        }
        for(Pos pos: wallSet.walls){
            copiedMap[pos.r][pos.c] = 1;
        }
    }

    public void coloring(Pos pos, int count){
        if(pos.r >= rowMax || pos.r < 0 || pos.c >= colMax || pos.c < 0)
            return;
        if(copiedMap[pos.r][pos.c] != 0 && count != 0)
            return;
        copiedMap[pos.r][pos.c] = 2;
        numOfVirus++;
        for(int i=0;i<4;i++){
            coloring(new Pos(pos.r + dirR[i], pos.c + dirC[i]), count+1);
        }
    }

    public void demo(){
        calCanWallAndWall();
        calWallSetList(0, -1, new ArrayList<Pos>());
        for(WallSet wallSet: wallSetList){
            makeCopiedMap(wallSet);
            numOfVirus = 0;
            for(Pos pos: initialVirusPoses)
                coloring(pos, 0);
            int nowCount = rowMax * colMax - numOfVirus - numOfWall - 3;
            if(nowCount > maxCount)
                maxCount = nowCount;
        }
    }

    public static void main(String[] args) throws IOException {
        Main main = new Main();
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] inputs = br.readLine().split(" ");
        main.rowMax = Integer.parseInt(inputs[0]);
        main.colMax = Integer.parseInt(inputs[1]);
        main.originMap = new int[main.rowMax][main.colMax];
        main.copiedMap = new int[main.rowMax][main.colMax];
        for(int r=0;r<main.rowMax;r++){
            inputs = br.readLine().split(" ");
            for(int c=0;c<main.colMax;c++){
                main.originMap[r][c] = Integer.parseInt(inputs[c]);
            }
        }
        main.demo();
        System.out.println(main.maxCount);
    }
}