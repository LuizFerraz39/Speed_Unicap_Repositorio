class Pessoa:
    def __init__(self, nome, idade, sexo, salario):
        self.nome = nome
        self.idade = idade
        self.sexo = sexo
        self.salario = salario

    def apresentar(self):
        print('Ola, meu nome e:', self.nome)


p1 = Pessoa('Carlos', 19, 'm', 4500)
p1.apresentar()

p2 = Pessoa('Beatriz', 20, 'f', 6000)
p2.apresentar()

p1.peso = 70.52

print(p1.peso)