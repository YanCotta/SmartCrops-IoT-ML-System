## ✅ Entrega 2: Estimativa de Custo na Nuvem AWS - CONCLUÍDA

### Comparativo de Custos: US East (Ohio) vs. São Paulo (Brasil)

Para esta análise, estimamos o custo mensal para hospedar a API da FarmTech Solutions em um servidor Linux utilizando a Calculadora de Preços da AWS. As especificações exigidas foram 2 vCPUs, 1 GiB de Memória e 50 GB de armazenamento SSD de uso geral, sob um modelo de preços On-Demand (Sob Demanda).

A comparação entre as regiões **US East (Ohio)** e **South America (São Paulo)** produziu os seguintes resultados, conforme detalhado na estimativa oficial da AWS.

| Região | Custo Mensal (USD) |
| :--- | :--- |
| **US East (Ohio)** | **US$ 11,59** |
| **South America (São Paulo)** | **US$ 19,86** |

*(Nota: Os custos são estimativas referentes a Agosto de 2025 e podem variar. Os detalhes completos da estimativa estão nos screenshots abaixo.)*

**Screenshot da Estimativa Oficial da AWS:**
![Comparativo de custos para regiões da AWS](entregavel_2/aws_comparison_cost.png)

**Screenshot do Custo Base da AWS:**
![Custo Base da AWS](entregavel_2/aws_baseline_cost.png)

---

### Justificativa e Escolha Final

**1. Análise de Custos:**
A região de **US East (Ohio)** é aproximadamente **71% mais barata** do que a região de São Paulo para os mesmos recursos computacionais. De uma perspectiva puramente financeira, o servidor baseado nos EUA oferece uma economia significativa.

**2. Justificativa Técnica e Legal:**
Apesar da considerável vantagem de custo da região de Ohio, a escolha estratégica correta para a FarmTech Solutions é hospedar o servidor em **São Paulo**. A justificativa baseia-se em dois fatores críticos e inegociáveis:

* **Baixa Latência para Dados de IoT**: A eficácia do sistema depende do recebimento e processamento de dados em tempo real de sensores localizados em uma fazenda no Brasil. Hospedar a API em São Paulo reduz drasticamente a latência da rede, garantindo processamento imediato dos dados e alertas ágeis. O atraso na conexão com um servidor nos EUA poderia invalidar o propósito de um sistema de monitoramento em tempo real.

* **Soberania de Dados e Conformidade com a LGPD**: A legislação brasileira, especificamente a Lei Geral de Proteção de Dados (LGPD), impõe regras estritas sobre o armazenamento e processamento de dados. Dados de produção agrícola podem ser considerados informações estratégicas e sensíveis. Armazená-los fora do Brasil introduz riscos legais e de conformidade significativos. Ao escolher a região de São Paulo, a FarmTech Solutions garante a aderência às leis locais, protegendo a si mesma e seus clientes.

**Conclusão:**
Para uma aplicação de IoT e Machine Learning onde o desempenho em tempo real e a conformidade legal são primordiais, os benefícios da baixa latência e da soberania de dados superam em muito o custo operacional mais elevado. Portanto, **São Paulo é a região recomendada e necessária para esta implementação.**
