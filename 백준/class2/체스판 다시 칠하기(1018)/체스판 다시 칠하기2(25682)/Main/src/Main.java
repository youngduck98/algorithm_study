import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
    public int[][] makeSumOfdiff(int[][] diff){
        int[][] ret = new int[diff.length][diff[0].length];

        ret[0][0] = diff[0][0];

        for(int c=1;c<diff[0].length;c++)
            ret[0][c] = ret[0][c-1] + diff[0][c];
        for(int r=1;r<diff.length;r++)
            ret[r][0] = ret[r-1][0] + diff[r][0];

        for(int r=1;r<diff.length;r++){
            for(int c=1;c<diff[0].length;c++){
                ret[r][c] = ret[r-1][c] + ret[r][c-1] - ret[r-1][c-1]
                        + diff[r][c];
            }
        }
        return ret;
    }

    public String nextString(String s){
        if(s.equals("W"))
            return "B";
        else if(s.equals("B"))
            return "W";
        throw new IllegalArgumentException();
    }

    public String[][] makeCheck(String[][] map, String start){
        String[][] ret = new String[map.length][map[0].length];

        ret[0][0] = start;

        for(int r=1;r<ret.length;r++){
            ret[r][0] = nextString(ret[r-1][0]);
        }

        for(int r=0;r<map.length;r++){
            for(int c=1;c<map[0].length;c++){
                ret[r][c] = nextString(ret[r][c-1]);
            }
        }

        return ret;
    }

    public int stringCompare(String s1, String s2){
        if(s1.equals(s2))
            return 0;
        return 1;
    }

    public int[][] makediff(String[][] map, String start){
        String[][] check = makeCheck(map, start);
        int[][] ret = new int[map.length][map[0].length];
        for(int r=0;r<map.length;r++){
            for(int c=0;c<map[0].length;c++){
                ret[r][c] = stringCompare(map[r][c], check[r][c]);
            }
        }
        return ret;
    }

    public static void main(String[] args) throws IOException {
        String[][] map;
        int[][] diff1;
        int[][] diff2;
        int[][] sum1;
        int[][] sum2;
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] input = br.readLine().split(" ");
        int maxRow = Integer.parseInt(input[0]);
        int maxCol = Integer.parseInt(input[1]);
        int size = Integer.parseInt(input[2]);
        map = new String[maxRow][maxCol];

        for(int r=0;r<maxRow;r++){
            String[] row = br.readLine().split("");
            for(int c=0;c<maxCol;c++){
                map[r][c] = row[c];
            }
        }

        Main main = new Main();
        diff1 = main.makediff(map, "W");
        diff2 = main.makediff(map, "B");
        sum1 = main.makeSumOfdiff(diff1);
        sum2 = main.makeSumOfdiff(diff2);

        int min1 = sum1[size-1][size-1];
        int min2 = sum2[size-1][size-1];

        for(int c=1;c<=map[0].length-size;c++){
            int now1 = sum1[size-1][c+size-1] - sum1[size-1][c-1];
            int now2 = sum2[size-1][c+size-1] - sum2[size-1][c-1];
            if(min1 > now1)
                min1 = now1;
            if(min2 > now2)
                min2 = now2;
        }

        for(int r=1;r<=map.length-size;r++){
            int now1 = sum1[r+size-1][size-1] - sum1[r-1][size-1];
            int now2 = sum2[r+size-1][size-1] - sum2[r-1][size-1];
            if(min1 > now1)
                min1 = now1;
            if(min2 > now2)
                min2 = now2;
        }

        for(int r=1;r<=map.length-size;r++){
            for(int c=1;c<=map[0].length-size;c++){
                int now1 = sum1[r+size-1][c+size-1] -
                        (sum1[r+size-1][c-1] + sum1[r-1][c+size-1] - sum1[r-1][c-1]);
                int now2 = sum2[r+size-1][c+size-1] -
                        (sum2[r+size-1][c-1] + sum2[r-1][c+size-1] - sum2[r-1][c-1]);
                if(min1 > now1)
                    min1 = now1;
                if(min2 > now2)
                    min2 = now2;
            }
        }

        System.out.println(Math.min(min1, min2));
    }
}