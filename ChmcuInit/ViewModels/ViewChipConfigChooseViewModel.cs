using Prism.Mvvm;
using Prism.Regions;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ChmcuInit.ViewModels
{
    public class ViewChipConfigChooseViewModel : BindableBase , INavigationAware
    {


        public ViewChipConfigChooseViewModel()
        {
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
            ProjectType = navigationContext.Parameters.GetValue<string>("Type");
        }
    }
}
