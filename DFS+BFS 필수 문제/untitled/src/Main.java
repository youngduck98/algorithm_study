import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;

class Pos{
    int r;
    int c;
    int count;

    public Pos(int r, int c, int count){
        this.r = r;
        this.c = c;
        this.count = count;
    }

    public boolean posCheck(int r, int c){
        return this.r == r && this.c == c;
    }

    public Pos movedFrom(int dir, int[] dirR, int[] dirC){
        return new Pos(this.r + dirR[dir],
                this.c + dirC[dir],
                this.count + 1);
    }

    public boolean checkAvailAtMap(char[][] map){
        if(this.r >= map.length || this.r < 0)
            return false;
        if(this.c >= map[0].length || this.c < 0)
            return false;
        return map[this.r][this.c] == '1';
    }
}

public class Main {
    char[][] map;
    int[] dirR = {0, 1, 0, -1};
    int[] dirC = {1, 0, -1, 0};

    public int BFS(){
        LinkedList<Pos> nowQue = new LinkedList<>();
        nowQue.add(new Pos(0, 0, 1));
        map[0][0] = '0';
        while(!nowQue.isEmpty()){
            Pos nowPos = nowQue.removeFirst();
            if(nowPos.posCheck(map.length-1, map[0].length-1)){
                return nowPos.count;
            }
            for(int i=0;i<4;i++){
                Pos addedPos = nowPos.movedFrom(i, dirR, dirC);
                if(addedPos.checkAvailAtMap(map)) {
                    map[addedPos.r][addedPos.c] = '0';
                    nowQue.addLast(addedPos);
                }
            }
        }
        return -1;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] input = br.readLine().split(" ");
        int rowMax = Integer.parseInt(input[0]);
        int colMax = Integer.parseInt(input[1]);
        Main main = new Main();
        main.map = new char[rowMax][colMax];
        for(int r=0;r<main.map.length;r++){
            String strInput = br.readLine();
            for(int c=0;c<main.map[0].length;c++){
                main.map[r][c] = strInput.charAt(c);
            }
        }
        System.out.println(main.BFS());
    }
}