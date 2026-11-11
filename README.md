# Bengala Inteligente

Bengala com sensor ultrassônico que avisa, por sons, a que distância está um obstáculo à frente. Quanto mais perto, mais rápidos os bipes.

> Trabalho da VT — N202 Robótica e Automação Inteligentes · Prof. Milton Miranda Neto

---

## 1. O problema real

**Quem é afetado:** pessoas com deficiência visual. Segundo a Pesquisa Nacional de Saúde 2019 do IBGE, 3,4% da população com 2 anos ou mais (cerca de 6,98 milhões de brasileiros) declarou ter muita dificuldade ou nenhuma capacidade de enxergar (IBGE, 2021).

**Onde acontece:** em calçadas, ruas, transporte, campus e ambientes internos, em qualquer deslocamento a pé.

**Por que importa:** a bengala longa detecta o que ela toca, principalmente no nível do chão. Obstáculos fora desse alcance (placas, galhos, toldos, portas abertas, objetos na altura do tronco ou da cabeça) podem passar despercebidos e causar batidas, quedas e insegurança, o que reduz a autonomia de quem se desloca sozinho. Em uma pesquisa com 307 pessoas cegas ou legalmente cegas (a maioria nos EUA), 13% relataram bater a cabeça em obstáculos pelo menos uma vez por mês, e o uso de cão-guia não protegeu mais do que o da bengala longa contra esses acidentes (MANDUCHI; KURNIAWAN, 2011).

**Como é tratado hoje:** bengala longa, cão-guia e acompanhante. Existem dispositivos eletrônicos específicos, mas nem sempre são acessíveis.

**Nossa proposta:** acoplar à bengala um sensor de distância e um aviso sonoro. O usuário é avisado de obstáculos à frente antes de encostar neles, e o aviso fica mais urgente conforme a distância diminui.

---

## 2. Componentes

| Componente | Função |
|---|---|
| Arduino Uno | Lê o sensor, filtra e comanda o buzzer |
| Sensor ultrassônico HC-SR04 | Mede a distância do obstáculo |
| Buzzer ativo 5V | Aviso sonoro |
| Protoboard | Conexões do circuito |
| Jumpers macho-macho e macho-fêmea | Ligações entre sensor, protoboard e Arduino |
| Caixa | Aloja o circuito, fixada na bengala |
| Abraçadeiras | Fixação da protoboard na caixa |
| Pilhas | Alimentação própria do Arduino |

---

## 3. Esquema de ligação

| HC-SR04 | Arduino Uno |
|---|---|
| VCC | 5V |
| TRIG | D9 |
| ECHO | D10 |
| GND | GND |

| Buzzer | Arduino Uno |
|---|---|
| + (perna longa) | D8 |
| − | GND |

```
            Arduino Uno
          ┌─────────────┐
 HC-SR04  │             │
  VCC ────┤ 5V          │
  TRIG ───┤ D9          │
  ECHO ───┤ D10         │
  GND ────┤ GND         │
          │             │
 Buzzer   │             │
  (+) ────┤ D8          │
  (−) ────┤ GND         │
          └─────────────┘
```

Os pinos estão definidos em `src/Bengala.h`.

**Segurança:** somente baixa tensão (alimentação por pilhas; o circuito opera em 5 V), com terra comum. Nenhuma parte do projeto usa tensão de rede.

---

## 4. Instruções de uso

### Gravar o código (PlatformIO)

1. Instale o [VS Code](https://code.visualstudio.com/) e a extensão **PlatformIO IDE**.
2. Clone o projeto e abra a pasta no VS Code:
   ```bash
   git clone https://github.com/fssantos-beep/Bengala-inteligente.git
   ```
3. Monte o circuito conforme a seção 3 e conecte o Arduino Uno ao computador por USB (só para gravar o código).
4. Clique em **Upload** do PlatformIO (ou rode `pio run -t upload`).
5. Para acompanhar as leituras, abra o monitor serial em **115200 baud** (`pio device monitor`). Aparecem linhas como `Distancia: 42 cm`.

Na Arduino IDE: crie um sketch, copie `src/main.cpp` para o `.ino`, coloque `Bengala.h` e `Bengala.cpp` na mesma pasta e selecione a placa **Arduino Uno**.

### Usar

Ligue a bengala com as pilhas (não precisa do notebook) e aponte o sensor para a frente. O som muda conforme a distância:

| Distância do obstáculo | Som |
|---|---|
| acima de 150 cm | silêncio |
| 81 a 150 cm | bipes lentos |
| 31 a 80 cm | bipes médios |
| até 30 cm | bipes rápidos |

Para testar, aproxime a mão do sensor e confira cada faixa.

---

## 5. Referências

Dados, estudos e autores citados neste projeto:

IBGE. **PNS 2019: país tem 17,3 milhões de pessoas com algum tipo de deficiência**. Agência IBGE Notícias, Rio de Janeiro, 26 ago. 2021. Disponível em: https://agenciadenoticias.ibge.gov.br/agencia-sala-de-imprensa/31445-pns-2019-pais-tem-17-3-milhoes-de-pessoas-com-algum-tipo-de-deficiencia.html. Acesso em: nov. 2026.
- Usado para: percentual e número de brasileiros com deficiência visual (3,4%, cerca de 6,98 milhões).

MANDUCHI, R.; KURNIAWAN, S. **Mobility-related accidents experienced by people with visual impairment**. Insight: Research and Practice in Visual Impairment and Blindness, v. 4, n. 2, 2011. Disponível em: https://users.soe.ucsc.edu/~manduchi/papers/MobilityAccidents.pdf. Acesso em: nov. 2026.
- Usado para: frequência de acidentes na altura da cabeça (13% ao menos uma vez por mês) e comparação entre cão-guia e bengala longa. A pesquisa ouviu 307 pessoas, a maioria nos EUA, e não representa necessariamente o Brasil.
