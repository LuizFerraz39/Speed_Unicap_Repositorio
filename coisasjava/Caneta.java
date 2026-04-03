package Aula_27_02;

public class Caneta {
    public String marca;
    private String cor;
    private String modelo;

    public Caneta(String marca, String cor, String modelo){
        this.marca = marca;
        this.cor = cor;
        this.modelo = modelo;
    }

    //GETS E SETS

    public String getCor(){
        return cor;
    }

    public void setCor(String cor){
        this.cor = cor;
    }

    public String getModelo(){
        return this.modelo;
    }

    public void setModelo(String modelo){
        this.modelo = modelo;
    }
}
