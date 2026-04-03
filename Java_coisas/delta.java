public class delta {
    double a;
    double b;
    double c;

    public delta(double a, double b, double c){
        this.a = a;
        this.b = b;
        this.c = c;
    }

    public double calcular_delta(){
        double resultado;
        resultado = (b*b)-(4*a*c);
        return resultado;
    }
}

