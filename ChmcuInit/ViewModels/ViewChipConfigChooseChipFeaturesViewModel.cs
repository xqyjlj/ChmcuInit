using ChmcuInit.Views;
using Prism.Mvvm;
using Prism.Regions;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ChmcuInit.ViewModels
{
    public class ViewChipConfigChooseChipFeaturesViewModel : BindableBase
    {
        private readonly IRegionManager regionManger;

        public ViewChipConfigChooseChipFeaturesViewModel(IRegionManager regionManger)
        {
            this.regionManger = regionManger;        
        }
    }
}
