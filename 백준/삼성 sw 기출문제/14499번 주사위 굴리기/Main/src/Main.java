import java.io.BufferedReader;
        import java.io.IOException;
        import java.io.InputStreamReader;

/**
 *  2       2
 *5 1 3 ->6 5 1
 *  4       4
 *  6       3
 */

class Dice{
    int upper = 0;
    int north = 0;
    int east = 0;
    int south = 0;
    int west = 0;
    int bellow = 0;
    int rowPos = 0;
    int colPos = 0;

    public Dice(int rowPos, int colPos){
        this.rowPos = rowPos;
        this.colPos = colPos;
    }

    public int roll(int dir, int num){
        switch (dir){
            case 1: rollRight(); break;
            case 4: rollDown(); break;
            case 2: rollLeft(); break;
            case 3: rollUpper(); break;
        }
        if(num == 0)
            return bellow;
        bellow = num;
        return 0;
    }

    public void rollRight(){
        //upper, north, east, south, west, bellow
        //123456 -> 521463
        int upper = this.upper;
        this.upper = this.west;
        this.west = this.bellow;
        this.bellow = this.east;
        this.east = upper;
    }

    public void rollLeft(){
        int upper = this.upper;
        this.upper = this.east;
        this.east = this.bellow;
        this.bellow = this.west;
        this.west = upper;
    }

    public void rollUpper(){
        int upper = this.upper;
        this.upper = this.south;
        this.south = this.bellow;
        this.bellow = this.north;
        this.north = upper;
    }

    public void rollDown(){
        int upper = this.upper;
        this.upper = this.north;
        this.north = this.bellow;
        this.bellow = this.south;
        this.south = upper;
    }
}

class Map{
    int[][] map;
    static int[] dirR = {0, 0, -1, 1};
    static int[] dirC = {1, -1, 0, 0};
    Dice dice;

    public Map(int[][] map, Dice dice){
        this.map = map;
        this.dice = dice;
    }

    public void moveIfAvail(int dir){
        int nextR = dice.rowPos + dirR[dir-1];
        int nextC = dice.colPos + dirC[dir-1];

        if(nextR < map.length && nextR >= 0 &&
                nextC < map[0].length && nextC >= 0) {
            dice.rowPos = nextR;
            dice.colPos = nextC;
            map[dice.rowPos][dice.colPos] = dice.roll(dir, map[dice.rowPos][dice.colPos]);
            System.out.println(dice.upper);
        }
    }

    public void move(String[] moveArr){
        for(String dir: moveArr){
            //System.out.println("dir: " + dir);
            moveIfAvail(Integer.parseInt(dir));
        }
    }
}

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] input = br.readLine().split(" ");
        int maxRow = Integer.parseInt(input[0]);
        int maxCol = Integer.parseInt(input[1]);
        int posR = Integer.parseInt(input[2]);
        int posC = Integer.parseInt(input[3]);

        int[][] map = new int[maxRow][maxCol];
        for(int r=0;r<maxRow;r++){
            String[] row = br.readLine().split(" ");
            for(int c=0;c<maxCol;c++){
                map[r][c] = Integer.parseInt(row[c]);
            }
        }

        Dice dice = new Dice(posR, posC);
        Map gameMap = new Map(map, dice);
        gameMap.move(br.readLine().split(" "));
    }
}