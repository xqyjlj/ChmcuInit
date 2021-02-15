using Prism.Mvvm;
using Prism.Regions;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ChmcuInit.Models;
using ChmcuInit.Service;
using System.Windows;
using Prism.Commands;
using System.Collections.ObjectModel;

namespace ChmcuInit.ViewModels
{
    public class ViewChipConfigChooseViewModel : BindableBase, INavigationAware
    {
        private readonly IRegionManager regionManger;
        public ViewChipConfigChooseViewModel(IRegionManager regionManger)
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
            ProjectType = navigationContext.Parameters.GetValue<string>("Type");
            if (ProjectType == @"Chip")
            {
                regionManger.RequestNavigate("ViewChipConfigChooseContentRegion", "ViewChipConfigChooseChip");
            }
        }
    }
}
