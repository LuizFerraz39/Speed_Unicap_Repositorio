package Aula_27_02;

public class aula_visibilidade {

    public static void main(String[] args){

        Caneta c1 = new Caneta("BIC", "caneta azul, azul caneta", "Esferográfica");

        System.out.println(c1.marca);
        System.out.println(c1.getCor());
        System.out.println(c1.getModelo());
    }

}
