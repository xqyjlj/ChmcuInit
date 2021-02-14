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
    public class ViewChipConfigViewModel : BindableBase, INavigationAware
    {
        private readonly IRegionManager regionManger;
        
        
        public ViewChipConfigViewModel(IRegionManager regionManger)
        {
            this.regionManger = regionManger;
        }

        public bool IsNavigationTarget(NavigationContext navigationContext)
        {
            return true;
        }

        public void OnNavigatedFrom(NavigationContext navigationContext)
        {
            
        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            string ProjectType;
            NavigationParameters param = new NavigationParameters();
            ProjectType = navigationContext.Parameters.GetValue<string>("Type");
            param.Add("Type", ProjectType);
            regionManger.RequestNavigate("ChipConfigViewContentRegion", "ViewChipConfigChoose", param);
        }
    }
}
