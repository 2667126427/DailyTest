public class _13 {
    private static void printReverseMatrix(int[][] matrix) {
        for (int rows = matrix.length, cols = matrix[0].length, i = cols - 1; i >= 0; --i) {
            for (int j = rows - 1; j >= 0; --j) {
                System.out.print(matrix[j][i] + " ");
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        int[][] test = {
                {1,2,3,4,5,6},
                {7,8,9,1,2,4}
        };
        printReverseMatrix(test);
    }
}
