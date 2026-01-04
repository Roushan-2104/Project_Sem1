

---

# 🇮🇳 Indian Income Tax Calculator (FY 2025-26)

A robust C program designed to calculate income tax based on the **New Tax Regime** slabs for the Financial Year 2025-26 (Assessment Year 2026-27). This tool handles standard deductions, rebates, surcharges, and complex marginal relief calculations automatically.

## 📋 Key Features

* **New Tax Regime Slabs:** Implements the latest slab rates introduced in the Union Budget.
* **Standard Deduction:** Automatically applies the flat deduction of **₹75,000** for salaried individuals.
* **Section 87A Rebate:** Incorporates the increased rebate limit, ensuring **NIL tax** for taxable income up to **₹12,00,000**.
* **Marginal Relief:** Includes logic to handle edge cases where income slightly exceeds ₹12 Lakhs, ensuring tax payable does not exceed the income earned above the threshold.
* **Surcharges:** Automatically calculates surcharges for High Net-worth Individuals (HNI) with income exceeding ₹50 Lakhs, ₹1 Crore, and ₹2 Crores.
* **Cess Calculation:** Applies the mandatory 4% Health and Education Cess on the final tax payable.

---

## 📊 Tax Slabs (FY 2025-26)

The program calculates tax based on the following net taxable income slabs (after Standard Deduction):

| Annual Income Range | Tax Rate |
| --- | --- |
| Upto ₹4,00,000 | **NIL** |
| ₹4,00,001 - ₹8,00,000 | **5%** |
| ₹8,00,001 - ₹12,00,000 | **10%** |
| ₹12,00,001 - ₹16,00,000 | **15%** |
| ₹16,00,001 - ₹20,00,000 | **20%** |
| ₹20,00,001 - ₹24,00,000 | **25%** |
| Above ₹24,00,000 | **30%** |

---

## ⚙️ Logic & Formulas

The program follows a sequential logic flow to determine the final liability:

1. **Net Taxable Income:**

<img width="331" height="50" alt="image" src="https://github.com/user-attachments/assets/7b077423-1303-4180-80c5-b3280418e5da" />

2. **Base Tax Calculation:**
The program iterates through the slabs to calculate the gross tax.
3. **Surcharge Application:**
If a surcharge (10%, 15%, or 25%) is added to the Gross Tax.
4. **Marginal Relief Check:**
If income is between ₹12,00,000 and ₹12,75,000, the program compares calculated tax against excess income:
<img width="331" height="50" alt="image" src="https://github.com/user-attachments/assets/6c3535c6-e28a-427c-a8dd-9178d4abd078" />

6. **Final Cess:**

<img width="331" height="50" alt="image" src="https://github.com/user-attachments/assets/59290f28-2d4d-4219-8d8a-7633d5d81ec9" />

---

## 🚀 How to Run

### Prerequisites

* A C compiler (GCC recommended).

### Compilation

Open your terminal or command prompt and run:

```bash
gcc Taxation.c -o tax_calculator

```

### Execution

Run the executable:

```bash
# On Windows
tax_calculator.exe

# On Linux/macOS
./tax_calculator

```

---

## 🧪 Usage Examples

**Scenario 1: Income within Rebate Limit**

* **Input:** ₹12,75,000
* **Logic:** 12.75L - 75k = 12L.
* **Output:** `Your Payable Tax is ₹0.00`

**Scenario 2: Marginal Relief Case**

* **Input:** ₹12,80,000
* **Logic:** 12.8L - 75k = 12.05L. (Net Income is slightly above 12L).
* **Output:** The tax will be calculated on the excess ₹5,000 rather than the full slab rate, preventing a tax cliff.

**Scenario 3: High Income**

* **Input:** ₹24,75,000
* **Logic:** 24.75L - 75k = 24L. Income hits the 25% slab.
* **Output:** Calculates cumulative tax for all slabs up to 24L + 4% Cess.

---

## ⚠️ Disclaimer

> This software is for educational and estimation purposes only. While it follows the FY 2025-26 structure, tax laws are subject to amendments. Please consult a qualified Chartered Accountant (CA) or financial advisor for official tax filing.

---

**Would you like me to generate a set of unit tests to verify the "Marginal Relief" logic in this code?**
