import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

class Pos{
    public Pos(int r, int c){
        this.r = r;
        this.c = c;
    }
    int r;
    int c;
}

class Condition{
    public Condition(){
        addedPos = new ArrayList<>();
        banned = new HashSet<>();
    }
    public Condition(Condition origin){
        addedPos = new ArrayList<>(origin.addedPos);
        banned = new HashSet<>(origin.banned);
    }
    List<Pos> addedPos;
    Set<Pos> banned;

    public void addPos(Pos pos, int maxWidth, List<Pos> posPool){
        addedPos.add(pos);
        if(pos.c > 0){
            banned.add(posPool.get(pos.r*maxWidth + pos.c - 1));
        }
        if(pos.c < maxWidth - 1)
            banned.add(posPool.get(pos.r*maxWidth + pos.c + 1));
        banned.add(pos);
    }

    public int find(boolean[][] map, int i, List<Pos> posPool){
        for(int r=0;r<map.length;r++){
            if(i > 0 && (map[r][i-1] || addedPos.contains(posPool.get(r *map[0].length + i-1)))) {
                i--;
                continue;
            }
            if(i < map[0].length && (map[r][i] || addedPos.contains(posPool.get(r*map[0].length + i))))
                i++;
        }
        return i;
    }

    public boolean right(boolean[][] map, List<Pos> posPool){
        for(int i=0;i<map[0].length + 1;i++){
            if(i == find(map, i, posPool)) {
                continue;
            }
            return false;
        }
        return true;
    }

    public void addAvailCondition(Set<Pos> originBan, boolean[][] map,
                                  LinkedList<Condition> queue, List<Pos> posPool){
        Pos last = posPool.get(posPool.size()-1);
        if(this.addedPos.size() >= 3)
            return;
        if(!addedPos.isEmpty())
            last = addedPos.get(addedPos.size() -1);
        for(int r=0;r<map.length;r++){
            for(int c=0;c<map[0].length;c++){
                if(last.r * last.c + last.c >= r * (c+1) + c)
                    continue;
                Pos pos = posPool.get(r*map[0].length+c);
                if(originBan.contains(pos) || banned.contains(pos))
                    continue;
                Condition condition = new Condition(this);
                condition.addPos(pos, map[0].length, posPool);
                queue.add(condition);
            }
        }
    }
}

public class BFSMemoryFail {
    boolean[][] map;
    Set<Pos> originBan = new HashSet<>();
    List<Pos> posPool = new ArrayList<>();

    public BFSMemoryFail(boolean[][] map){
        this.map = map;
    }

    public void makeOriginBan(){
        for(int r=0;r<map.length;r++){
            for(int c=0;c<map[0].length;c++){
                if(c>0 && map[r][c]){
                    originBan.add(posPool.get(r*map[0].length +c -1));
                }
                if(c <map[0].length-1&&map[r][c]){
                    originBan.add(posPool.get(r*map[0].length + c + 1));
                }
                if(map[r][c])
                    originBan.add(posPool.get(r*map[0].length + c));
            }
        }
    }

    public void BFS(){
        for(int r=0;r< map.length;r++){
            for(int c=0;c<map[0].length;c++){
                posPool.add(new Pos(r,c));
            }
        }
        posPool.add(new Pos(0, -1));
        makeOriginBan();
        LinkedList<Condition> queue = new LinkedList<>();
        queue.add(new Condition());

        while(!queue.isEmpty()){
            Condition condition = queue.removeFirst();
            if(condition.right(map, posPool)){
                System.out.println(condition.addedPos.size());
                return;
            }
            if(condition.addedPos.size() > 3)
                break;

            condition.addAvailCondition(originBan, map, queue, posPool);
        }
        System.out.println(-1);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] inputs = br.readLine().split(" ");
        int colMax = Integer.parseInt(inputs[0]) - 1;
        int nowBranch = Integer.parseInt(inputs[1]);
        int rowMax = Integer.parseInt(inputs[2]);
        boolean[][] map = new boolean[rowMax][colMax];
        for(int i=0;i<nowBranch;i++){
            inputs = br.readLine().split(" ");
            int row = Integer.parseInt(inputs[0]) - 1;
            int col = Integer.parseInt(inputs[1]) -1;
            map[row][col] = true;
        }
        BFSMemoryFail main = new BFSMemoryFail(map);
        main.BFS();
    }
}