package Aula_27_02;

public class pizza {
    String nome;
    double valor;

    public pizza(String nome, double valor){
        this.nome = nome;
        this.valor = valor;
    }

    public double calcular(){
        return this.valor;
    }

    public double calcularComCupom(cupons c1){
        double desconto = 1 - c1.getDesconto();
        return this.valor * desconto;
    }
}
