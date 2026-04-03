package Aula_27_02;

public enum cupons {
    PRIMEIRACOMPRA(0.1, "Primeira compra"),
    CLIENTE10(0.3, "Compra de 10 pizzas"),
    LAELE(0.9, "Conhece demais o dono da pizzaria");

    double desconto;
    String motivo;

    cupons(double desconto, String motivo){
        this.desconto = desconto;
        this.motivo = motivo;
    }

    public double getDesconto(){
        return this.desconto;
    }

    public String getMotivo(){
        return this.motivo;
    }

}
