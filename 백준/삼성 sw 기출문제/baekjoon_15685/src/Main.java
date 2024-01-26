import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

class Pos{
    public final static int[] dirX = {1, 0, -1, 0};
    public final static int[] dirY = {0, -1, 0, 1};
    public Pos(int x, int y){
        this.x = x;
        this.y = y;
    }
    int x;
    int y;

    public Pos nextPos(int dir){
        return new Pos(x + dirX[dir], y+dirY[dir]);
    }
}

class Curve{
    List<Pos> posList = new ArrayList<>();
    List<Integer> dirList = new ArrayList<>();
    public Curve(Pos start, int dir, int generation, boolean reverse){
        posList.add(start);
        posList.add(start.nextPos(dir));
        dirList.add(dir);
        int count = 0;
        while(count < generation){
            Curve addedCurve = nextAdded(this, count, reverse);
            posList.addAll(addedCurve.posList);
            dirList.addAll(addedCurve.dirList);
            count++;
        }
    }

    public Curve(List<Pos> posList, List<Integer> dirList){
        this.posList = posList;
        this.dirList = dirList;
    }

    public Curve nextAdded(Curve curve, int beforeGeneration, boolean reverse){
        Pos last = curve.posList.get(curve.posList.size()-1);
        List<Pos> addedPosList = new ArrayList<>();
        List<Integer> addedDirList = new ArrayList<>();
        for(int i=curve.dirList.size()-1;i>=0;i--){
            int dir = (curve.dirList.get(i) + 1)%4;
            addedPosList.add(last.nextPos(dir));
            addedDirList.add(dir);
            last = addedPosList.get(addedPosList.size()-1);
        }

        return new Curve(addedPosList, addedDirList);
    }

}

class Map{
    Pos start;
    boolean[][] map;
    int count = 0;

    public Map(List<Curve> curves){
        int maxX = Integer.MIN_VALUE;
        int maxY = Integer.MIN_VALUE;
        int minX = Integer.MAX_VALUE;
        int minY = Integer.MAX_VALUE;

        for(Curve curve: curves){
            for(Pos pos: curve.posList){
                if(pos.x > maxX)
                    maxX = pos.x;
                if(pos.x < minX)
                    minX = pos.x;
                if(pos.y > maxY)
                    maxY = pos.y;
                if(pos.y < minY)
                    minY = pos.y;
            }
        }

        this.start = new Pos(minX, minY);
        map = new boolean[maxX-minX+1][maxY-minY+1];

        for(Curve curve: curves){
            for(Pos pos: curve.posList){
                map[pos.x-start.x][pos.y-start.y] = true;
            }
        }
        this.count = findRectangle();
    }

    public int findRectangle(){
        int count = 0;
        for(int r=0;r<map.length-1;r++){
            for(int c=0;c<map[0].length-1;c++){
                if(map[r][c] && map[r+1][c] && map[r][c+1] && map[r+1][c+1]) {
                    count++;
                }

            }
        }
        return count;
    }

    public void printMap(){
        for(int r=0;r<map.length;r++){
            for(int c=0;c<map[0].length;c++) {
                System.out.print((map[r][c] ? 1 : 0) + " ");
            }
            System.out.println();
        }
    }
}

public class Main {

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int numOfCurve = Integer.parseInt(br.readLine());
        List<Curve> curves = new ArrayList<>();
        for(int i=0;i<numOfCurve;i++){
            String[] inputs = br.readLine().split(" ");
            int x = Integer.parseInt(inputs[0]);
            int y = Integer.parseInt(inputs[1]);
            int dir = Integer.parseInt(inputs[2]);
            int generation = Integer.parseInt(inputs[3]);
            Curve curve = new Curve(new Pos(x, y), dir, generation, false);
            curves.add(curve);
        }
        Map map = new Map(curves);
        System.out.println(map.count);
    }
}