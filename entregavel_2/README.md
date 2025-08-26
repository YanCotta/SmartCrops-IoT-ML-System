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

**AWS Baseline Cost Screenshot:**
![AWS Baseline Cost](entregavel_2/aws_baseline_cost.png)

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

## ✅ Deliverable 2: AWS Cloud Cost Estimation - COMPLETED

### Cost Comparison: US East (Ohio) vs. São Paulo (Brazil)

For this analysis, we estimated the monthly cost to host the FarmTech Solutions API on a Linux server using the AWS Pricing Calculator. The required specifications were 2 vCPUs, 1 GiB of Memory, and 50 GB of general-purpose SSD storage, under an On-Demand pricing model.

The comparison between the **US East (Ohio)** and **South America (São Paulo)** regions yielded the following results, as detailed in the official AWS estimate.

| Region | Monthly Cost (USD) |
| :--- | :--- |
| **US East (Ohio)** | **$11.59** |
| **South America (São Paulo)** | **$19.86** |

*(Note: Costs are estimates as of August 2025 and may vary. Full estimate details are in the screenshots below.)*

**Official AWS Estimate Screenshot:**
**Screenshot da Estimativa Oficial da AWS:**
![Comparativo de custos para regiões da AWS](entregavel_2/aws_comparison_cost.png)

**AWS Baseline Cost Screenshot:**
![AWS Baseline Cost](entregavel_2/aws_baseline_cost.png)

---

### Justification and Final Choice

**1. Cost Analysis:**
The **US East (Ohio)** region is approximately **71% cheaper** than the São Paulo region for the same computing resources. From a purely financial perspective, the US-based server offers significant savings.

**2. Technical and Legal Justification:**
Despite the substantial cost advantage of the Ohio region, the correct strategic choice for FarmTech Solutions is to host the server in **São Paulo**. The justification is based on two critical, non-negotiable factors:

* **Low Latency for IoT Data**: The system's effectiveness hinges on receiving and processing real-time data from sensors on a Brazilian farm. Hosting the API in São Paulo drastically reduces network latency, ensuring immediate data processing and timely alerts. The delay from connecting to a server in the US could render the real-time monitoring system ineffective.

* **Data Sovereignty and LGPD Compliance**: Brazil's Lei Geral de Proteção de Dados (LGPD) imposes strict rules on data storage and processing. As agricultural production data can be considered sensitive and strategic, storing it outside of Brazil introduces significant legal and compliance risks. By choosing the São Paulo region, FarmTech Solutions guarantees adherence to local laws, protecting both the company and its clients.

**Conclusion:**
For a real-time IoT and ML application where performance and legal compliance are paramount, the benefits of low latency and data sovereignty far outweigh the higher operational cost. Therefore, **São Paulo is the recommended and required region for this deployment.**