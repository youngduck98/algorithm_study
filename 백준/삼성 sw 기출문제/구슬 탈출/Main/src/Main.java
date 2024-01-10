import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.LinkedList;
class ball{
    int r;
    int c;

    public ball(int r, int c){
        this.r = r;
        this.c = c;
    }

    public ball copy(){
        return new ball(r, c);
    }

    public void moveUp(int[][] map){
        map[r][c] = 0;
        while(map[r][c] != 1){
            if(map[r][c] == 2)
                return;
            r--;
        }
        r+=1;
        map[r][c] = 1;
    }

    public void moveDown(int[][] map){
        map[r][c] = 0;
        while(map[r][c] != 1){
            if(map[r][c] == 2)
                return;
            r++;
        }
        r-=1;
        map[r][c] = 1;
    }

    public void moveLeft(int[][] map){
        map[r][c] = 0;
        while(map[r][c] != 1){
            if(map[r][c] == 2)
                return;
            c--;
        }
        c+=1;
        map[r][c] = 1;
    }

    public void moveRight(int[][] map){
        map[r][c] = 0;
        while(map[r][c] != 1){
            if(map[r][c] == 2)
                return;
            c++;
        }
        c-=1;
        map[r][c] = 1;
    }
}

class RectangleBox{
    int[][] map; // 1, 0
    ball red;
    ball blue;

    int count;
    public RectangleBox(ball red, ball blue, int[][] map, int count){
        this.red = red;
        this.blue = blue;
        this.map = map;
        this.count = count;
    }

    public RectangleBox copy(){
        int[][] copiedMap = new int[map.length][map[0].length];
        for(int r = 0;r<map.length;r++){
            copiedMap[r] = Arrays.copyOf(map[r], map[r].length);
        }
        return new RectangleBox(red.copy(), blue.copy(), copiedMap, count);
    }

    public boolean checkEnd(){
        if(map[blue.r][blue.c] == 2 || map[red.r][red.c] == 2)
            return false;
        return true;
    }

    public boolean success(){
        return map[blue.r][blue.c] != 2 && map[red.r][red.c] == 2;
    }

    public boolean move(int i){
        switch (i){
            case 0: return moveUp();
            case 1: return moveRight();
            case 2: return moveDown();
            case 3: return moveLeft();
        }
        return false;
    }

    public boolean moveUp(){
        if(blue.r < red.r){
            blue.moveUp(map);
            red.moveUp(map);
        }
        else{
            red.moveUp(map);
            blue.moveUp(map);
        }
        return checkEnd();
    }

    public boolean moveDown(){
        if(blue.r > red.r){
            blue.moveDown(map);
            red.moveDown(map);
        }
        else{
            red.moveDown(map);
            blue.moveDown(map);
        }
        return checkEnd();
    }

    public boolean moveLeft(){
        if(blue.c < red.c){
            blue.moveLeft(map);
            red.moveLeft(map);
        }
        else{
            red.moveLeft(map);
            blue.moveLeft(map);
        }
        return checkEnd();
    }

    public boolean moveRight(){
        if(blue.c > red.c){
            blue.moveRight(map);
            red.moveRight(map);
        }
        else{
            red.moveRight(map);
            blue.moveRight(map);
        }
        return checkEnd();
    }
}

public class Main {
    public int bfs(RectangleBox box){
        LinkedList<RectangleBox> list = new LinkedList<>();
        list.add(box);

        while(!list.isEmpty()){
            for(int i=0;i<4;i++) {
                RectangleBox newBox = list.peekFirst().copy();
                if(newBox.move(i)) {
                    newBox.count += 1;
                    if(newBox.count < 10)
                        list.add(newBox);
                }
                else if(newBox.success()){
                    return newBox.count + 1;
                }
            }
            list.removeFirst();
        }
        return -1;
    }
    public static void main(String[] args) throws IOException {
        int rowMax;
        int colMax;
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] inputs = br.readLine().split(" ");
        rowMax = Integer.parseInt(inputs[0]);
        colMax = Integer.parseInt(inputs[1]);
        int[][] map = new int[rowMax][colMax];
        ball red = new ball(0, 0);
        ball blue = new ball(0, 0);

        for(int r=0;r<rowMax;r++){
            String line = br.readLine();
            for(int c=0;c<colMax;c++){
                switch (line.charAt(c)){
                    case '#': map[r][c] = 1; break;
                    case '.': map[r][c] = 0; break;
                    case 'B':
                        map[r][c] = 1;
                        blue.r = r;
                        blue.c = c;
                        break;
                    case 'R':
                        map[r][c] = 1;
                        red.r = r;
                        red.c = c;
                        break;
                    case 'O': map[r][c] = 2; break;
                }
            }
        }

        RectangleBox box = new RectangleBox(red, blue, map, 0);
        RectangleBox box2 = box.copy();
        Main main = new Main();
        System.out.println(main.bfs(box));
    }
}