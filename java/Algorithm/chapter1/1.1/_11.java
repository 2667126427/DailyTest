public class _11 {
    public static void printBooleanMatrix(boolean[][] matrix) {
        if (matrix == null || matrix.length == 0) return;
        System.out.print(" ");
        for (int i = 0, cols = matrix[0].length; i < cols; i++) {
            System.out.print(i);
        }
        for (int i = 0, rows = matrix.length, cols = matrix[0].length; i < rows; i++) {
            System.out.print(i);
            for (int j = 0; j < cols; j++) {
                System.out.print((matrix[i][j] ? "*" : " "));
            }
        }
    }
}
