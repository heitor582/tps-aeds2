import java.util.Scanner;

class Node {
    Node up, down, left, right = null;
    int value;

    public Node(Node up, Node down, Node left, Node right, int value) {
        this.up = up;
        this.down = down;
        this.left = left;
        this.right = right;
        this.value = value;
    }

    public Node(int value) {
        this.value = value;
    }

    public Node() {
    }
}

class DynamicMatrix {
    Node start;
    int col, row;

    public DynamicMatrix(int row, int col, int values[][]) {
        this.col = col;
        this.row = row;

        this.start = new Node(values[0][0]);
        Node pre = null;

        for (int i = 0; i < row; i++) {
            Node rowN = i == 0 ? this.start : new Node(values[i][0]);
            rowN.up = pre;
            if (pre != null) {
                pre.down = rowN;
            }
            Node cpy = rowN;
            for (int j = 1; j < col; j++) {
                Node node = new Node(values[i][j]);
                node.left = cpy;
                cpy.right = node;

                if (pre != null) {
                    node.up = cpy.up.right;
                    cpy.up.right.down = node;
                }

                cpy = node;
            }
            pre = rowN;
        }
    }

    DynamicMatrix soma(DynamicMatrix m) {
        if (this.row != m.row || this.col != m.col)
            return null;
        int arr[][] = new int[row][col];
        Node row1 = this.start;
        Node row2 = m.start;

        for (int i = 0; i < row; i++) {
            Node col1 = row1;
            Node col2 = row2;
            for (int j = 0; j < col; j++) {
                arr[i][j] = col1.value + col2.value;
                col1 = col1.right;
                col2 = col2.right;
            }
            row1 = row1.down;
            row2 = row2.down;
        }

        return new DynamicMatrix(row, col, arr);
    }

    DynamicMatrix multiplicacao(DynamicMatrix m) {
        if (m.row != this.col)
            return null;
        int arr[][] = new int[this.row][m.col];
        int i = 0;
        for(Node cur = this.start; cur != null; cur = cur.down, i++){
            int j = 0;
            for (Node col = m.start; col != null; col = col.right, j++) {
                int sum = 0;
                Node p = cur;
                for (Node row = col; row != null; row = row.down) {
                    sum += p.value * row.value;
                    p = p.right;
                }
                arr[i][j] = sum;
            }
        }

        return new DynamicMatrix(this.row, m.col, arr);
    }

    void mostrarDiagonalPrincipal() {
        Node cur = this.start;
        for (; cur != null && cur.down != null; cur = cur.down.right) {
            System.out.print(cur.value + " ");
        }
        System.out.println(cur.value + " ");
    }

    void mostrarDiagonalSecundaria() {
        Node cur = this.start;
        for (; cur != null && cur.right != null; cur = cur.right)
            ;
        for (; cur != null && cur.down != null; cur = cur.down.left) {
            System.out.print(cur.value + " ");
        }
        System.out.println(cur.value + " ");
    }

    void print() {
        for (Node row = this.start; row != null; row = row.down) {
            for (Node col = row; col != null; col = col.right) {
                System.out.print(col.value + " ");
            }
            System.out.println();
        }
    }
}

public class Matrix {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int cases = sc.nextInt();

        for (int i = 0; i < cases; i++) {
            int row = sc.nextInt();
            int col = sc.nextInt();
            int values[][] = new int[row][col];
            for (int j = 0; j < row; j++) {
                for (int k = 0; k < col; k++) {
                    values[j][k] = sc.nextInt();
                }
            }

            DynamicMatrix matrix = new DynamicMatrix(row, col, values);
            matrix.mostrarDiagonalPrincipal();
            matrix.mostrarDiagonalSecundaria();

            row = sc.nextInt();
            col = sc.nextInt();
            values = new int[row][col];

            for (int j = 0; j < row; j++) {
                for (int k = 0; k < col; k++) {
                    values[j][k] = sc.nextInt();
                }
            }
            DynamicMatrix matrix2 = new DynamicMatrix(row, col, values);

            (matrix.soma(matrix2)).print();
            (matrix.multiplicacao(matrix2)).print();
        }

        sc.close();
    }
}
