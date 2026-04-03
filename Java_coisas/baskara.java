import java.util.Scanner;

public class baskara {
    public static void main (String[] args) {

        Scanner scanner = new Scanner(System.in);

        System.out.println("Digite os coeficientes");
        System.out.println("A, B e C respectivamente:");

        double a = scanner.nextDouble();
        double b = scanner.nextDouble();
        double c = scanner.nextDouble();

        delta d1 = new delta(a,b,c);
        double dlt = d1.calcular_delta();
        if (dlt < 0){
            System.out.println("Impossivel ter raizes");
        }
        else{
            double x1 = ((-b) + Math.sqrt(dlt))/(2*a);
            double x2 = ((-b) - Math.sqrt(dlt))/(2*a);
            
            System.out.println("x1 : " + x1);
            System.out.println("x2 : " + x2);
        }

        scanner.close();
         

    }
}
