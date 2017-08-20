class GetLocks{
    int sum;
    int[][] board;
    boolean[] used;

    public GetLocks() {
        sum = 0;
        used = new boolean[9];
        board = new int[9][9];
        board[0][2] = board[2][0] = board[0][6] = board[6][0] = board[0][8] = board[8][0] = 1;
        board[2][6] = board[6][2] = board[2][8] = board[8][2] = 1;
        board[6][8] = board[8][6] = 1;
        board[1][7] = board[7][1] = board[3][5] = board[5][3] = 1;
    }

    private void search(int depth, int point, String from) {
        // 设置为true后要再设置回去，防止漏查
        used[point] = true;
        // 连接的点大于等于4个可以收录了
        if (depth >= 4) {
            ++sum;
            // 想看输出结果的可以解除注释重定向到文件里，要不然输会很慢的
            // System.out.println(from);
        }
        for (int i = 0; i < 9; i++) {
            if (used[i] || point == i) continue;
            if (board[point][i] == 0) {
                used[i] = true;
                search(depth + 1, i, from + "->" + i);
                used[i] = false;
            } else if (board[point][i] == 1) {
                //对于那些中间跨一个点的，我想的是比如0->1
                // 下一步的1可以到2就可以不要0->2的，二如果像1->0>2才收录，就是1已经used了
                used[i] = true;
                // 中间点已经使用，可以向下搜索
                if (used[(i + point) / 2]) {
                    search(depth + 1, i, from + "->" + i);
                }
                used[i] = false;
            }
        }
        // 复位
        used[point] = false;
    }

    public static void main(String[] args) {
        GetLocks sol = new GetLocks();
        // 分别从9个点出发
        for (int i = 0; i < 9; i++) {
            sol.search(1, i, String.valueOf(i));
        }
        System.out.println(sol.sum);
    }
}

