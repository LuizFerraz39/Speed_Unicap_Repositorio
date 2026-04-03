package Aula_27_02;

public class aula_enum {
    public static void main(String[] args){
        cupons c1 = cupons.PRIMEIRACOMPRA;

        System.out.println(c1);
        System.out.println(c1.getMotivo());

        cupons c2 = cupons.LAELE;

        System.out.println(c2.getMotivo());

        pizza p1 = new pizza("Calabreza", 35.0);

        System.out.println("O valor final da pizza e: " + p1.calcular());
        System.out.println("O valor final da pizza com cupom e: " + p1.calcularComCupom(c1));
        System.out.println("O valor final da pizza com cupom e: " + p1.calcularComCupom(c2));
        }
}
