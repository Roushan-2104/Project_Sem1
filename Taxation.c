#include <stdio.h>
#include <math.h>

/*

    _        ( FY - 2025-26 |TAX SLAB| )           _
   |_   Annual Income       _|_   Rate of tax (%)  _|
   |  Upto ₹4,00,000         |        NIL           |
   | ₹4,00,000 - ₹8,00,000   |        5%            |
   | ₹8,00,000 - ₹12,00,000  |        10%           |
   | ₹12,00,000 - ₹16,00,000 |        15%           |
   | ₹16,00,000 - ₹20,00,000 |        20%           |
   | ₹20,00,000 - ₹24,00,000 |        25%           |
   |_ Above ₹24,00,000      _|_       30%          _|

    Standard Deduction -> ₹75,000
    Maximum Rebate -> ₹60,000 ( Income upto ₹12,00,000 & Resident of India )
    Health and Education Cess ( 4% ) on Tax Payable.

*/

/* Macro to find the minimum of two numbers.
   Used later for Marginal Relief calculations.
*/
#define MIN(a, b) ((a) < (b) ? (a) : (b))

  
    

float taxSlab(float annIncome)
{
    int standDeduc = 75000;      // Standard Deduction is flat ₹75,000 for salaried employees
    float FTtax = 0; // Final Total Tax
    float netTxInc = annIncome - standDeduc; // Net Taxable Income
    float excIncome;             // Excess Income (used for marginal relief)
    float maxRebate = 60000;     // Max Rebate under Section 87A (Tax on ₹12L is ₹60k)
    float grsTtax = 0;               // Gross Tax before Cess
    float TtaxBCess = 0;      // Tax Before Cess
    
    // --- STEP 1: Calculate Base Tax based on Slabs ---

    // Slab 1: Upto ₹4L -> NIL Tax
    if (netTxInc <= 400000)
    {
        grsTtax = 0;
    }
    // Slab 2: ₹4L - ₹8L -> 5% Tax
    else if (netTxInc > 400000 && netTxInc <= 800000)
    {
        grsTtax = (netTxInc - 400000) * 0.05;
    }
    // Slab 3: ₹8L - ₹12L -> 10% Tax
    // Add ₹20,000 (Tax from previous 4L-8L slab: 4L * 5%)
    else if (netTxInc > 800000 && netTxInc <= 1200000)
    {
        grsTtax = ((netTxInc - 800000) * 0.10) + 20000;
    }
    // Slab 4: ₹12L - ₹16L -> 15% Tax
    // Add ₹60,000 (Cumulative tax from previous slabs: 20k + 40k)
    else if (netTxInc > 1200000 && netTxInc <= 1600000)
    {
        grsTtax = ((netTxInc - 1200000) * 0.15) + 40000 + 20000;
    }
    // Slab 5: ₹16L - ₹20L -> 20% Tax
    // Add ₹1,20,000 (Cumulative tax: 20k + 40k + 60k)
    else if (netTxInc > 1600000 && netTxInc <= 2000000)
    {
        grsTtax = ((netTxInc - 1600000) * 0.20) + 40000 + 20000 + 60000;
    }
    // Slab 6: ₹20L - ₹24L -> 25% Tax
    // Add ₹2,00,000 (Cumulative tax: 20k + 40k + 60k + 80k)
    else if (netTxInc > 2000000 && netTxInc <= 2400000)
    {
        grsTtax = ((netTxInc - 2000000) * 0.25) + 40000 + 20000 + 60000 + 80000;
    }
    // Slab 7: Above ₹24L -> 30% Tax
    // Add ₹3,00,000 (Cumulative tax from all previous slabs)
    else if (netTxInc > 2400000)
    {
        grsTtax = ((netTxInc - 2400000) * 0.30) + 40000 + 20000 + 60000 + 80000 + 100000;

        // --- STEP 2: Surcharge Calculations (For High Net Worth) ---
        // Surcharge is calculated on top of the Gross Tax
        
        if(netTxInc > 5000000 && netTxInc <= 10000000){
            // Income > 50L: 10% Surcharge
            grsTtax = (grsTtax * 0.10) + grsTtax;
        }
        else if(netTxInc > 10000000 && netTxInc <= 20000000){
            // Income > 1Cr: 15% Surcharge
            grsTtax = (grsTtax * 0.15) + grsTtax;
        }
        else if(netTxInc > 20000000 && netTxInc <= 50000000){
            // Income > 2Cr: 25% Surcharge
            grsTtax = (grsTtax * 0.25) + grsTtax;
        }
        else if(netTxInc > 50000000){
            // Income > 5Cr: 25% Surcharge (Capped at 25% in New Regime)
            grsTtax = (grsTtax * 0.25) + grsTtax;
        }
    }
    
    // --- STEP 3: Rebate (Sec 87A) and Marginal Relief ---
    
    // Check if income is within the transition zone for Rebate (12L to ~12.75L)
    if (netTxInc <= 1275000)
    {
        // Special Case: Marginal Relief
        // If income is slightly above ₹12L, the tax payable should not exceed 
        // the income earned *above* ₹12L.
        if (netTxInc <= 1275000 && netTxInc >= 1200000)
        {
            excIncome = netTxInc - 1200000; // Amount earned over 12L
            
            // Tax is the lower of: Calculated Tax OR The Excess Income
            float resTax = MIN(grsTtax, excIncome);
            
            // Apply 4% Cess
            FTtax = (resTax * 0.04) + resTax;
        }
        else
        {
            // Standard Rebate logic:
            // If Net Income <= 12L, Tax is 0 (Rebate applies).
            // TtaxBCess becomes 0 because MIN(tax, 60000) subtracts from tax.
            TtaxBCess = MIN(grsTtax, maxRebate);
            
            // Apply 4% Cess
            FTtax = (grsTtax - TtaxBCess) * 0.04; 
        }
    }
    // --- STEP 4: Standard Calculation for Higher Incomes ---
    else if (netTxInc > 1275000)
    {
        // No rebate applicable, add 4% Health & Education Cess directly
        FTtax = (grsTtax * 0.04) + grsTtax;
    }

    return FTtax;
}

int main()
{
    float annIncome;

    printf("Enter your Annual Income: ₹");
    scanf("%f", &annIncome);

    float TotalTax = taxSlab(annIncome);

    printf("Your Payable Tax is ₹%.2f", TotalTax);

    return 0;
}