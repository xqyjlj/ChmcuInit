using ChmcuInit.Models;
using Prism.Mvvm;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace ChmcuInit.Models
{
    public class ChipItemsModel: BindableBase
    {
        public McuFeature mcuFeature { get; set; }

        public string companyName { get; set; }

        public string familyName { get; set; }

        public string subFamilyName { get; set; }

        public string mcuName { get; set; }
    }
}
