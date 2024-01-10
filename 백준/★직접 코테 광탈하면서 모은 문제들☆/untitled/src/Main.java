import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

class Node{
    public Node(int index, int length){
        this.index = index;
        this.length = length;
    }
    int index;
    int length;
}

class MooTube{
    List<Node>[] network;
    boolean[] visited;
    int num = 0;

    public MooTube(List<Node>[] network){
        this.network = network;
        this.visited = new boolean[network.length];
    }

    public void findUSADO(int startIndex, int beforeValue, int k, int beforeIndex){
        if(!visited[startIndex] && beforeValue >= k && beforeValue != Integer.MAX_VALUE){
            num++;
        }
        for(Node node: network[startIndex]){
            if(beforeIndex == node.index)
                continue;
            findUSADO(node.index, Math.min(node.length, beforeValue), k, startIndex);
        }
    }

    public void addNetwork(int index1, int index2, int length){
        if(network[index1] == null)
            network[index1] = new ArrayList<>();
        network[index1].add(new Node(index2, length));
        if(network[index2] == null)
            network[index2] = new ArrayList<>();
        network[index2].add(new Node(index1, length));
    }

    public void initFlag(){
        this.visited = new boolean[this.network.length];
    }

    public void initNum(){
        this.num = 0;
    }
}

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] input = br.readLine().split(" ");
        int N = Integer.parseInt(input[0]);
        int Q = Integer.parseInt(input[1]);
        List<Node>[] network = new ArrayList[N+1];
        MooTube mooTube = new MooTube(network);
        for(int i=0;i<N-1;i++){
            input = br.readLine().split(" ");
            mooTube.addNetwork(
                    Integer.parseInt(input[0]),
                    Integer.parseInt(input[1]),
                    Integer.parseInt(input[2])
            );
        }
        for(int i=0;i<Q;i++){
            input = br.readLine().split(" ");
            mooTube.findUSADO(Integer.parseInt(input[1]),Integer.MAX_VALUE,
                    Integer.parseInt(input[0]), 0);
            System.out.println(mooTube.num);
            mooTube.initFlag();
            mooTube.initNum();
        }
    }
}