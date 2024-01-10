import java.util.LinkedList;

public class DFS{
    boolean[] visited;
    int[][] network;
    public void example(){
        LinkedList<Integer> stack = new LinkedList<>();
        int start = 0;
        visited[start] = true;
        for(int node: network[start]){
            stack.push(node);
        }
        while(!stack.isEmpty()){
            int nowNode = stack.pop();

            visited[nowNode] = true;
            for(int node: network[nowNode]){
                if(visited[node])
                    continue;
                stack.push(node);
            }
        }
    }
}