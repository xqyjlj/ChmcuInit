using Prism.Commands;
using Prism.Mvvm;
using Prism.Regions;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ChmcuInit.ViewModels
{
    public class ViewStartViewModel : BindableBase
    {
        private readonly IRegionManager regionManger;

        public DelegateCommand CreateProjectChipCommand { get; private set; }

        public DelegateCommand CreateProjectBoardCommand { get; private set; }

        public ViewStartViewModel(IRegionManager regionManger)
        {
            this.regionManger = regionManger;
            CreateProjectChipCommand = new DelegateCommand(CreateProjectChip);
            CreateProjectBoardCommand =new DelegateCommand(CreateProjectBoard);
        }

        private void CreateProjectChip()
        {
            NavigationParameters param = new NavigationParameters();
            param.Add("Type", "Chip");
            regionManger.RequestNavigate("MainWindowContentRegion", "ViewChipConfig", param);
        }
        
        private void CreateProjectBoard()
        {
            NavigationParameters param = new NavigationParameters();
            param.Add("Type", "Board");
            regionManger.RequestNavigate("MainWindowContentRegion", "ViewChipConfig", param);
        }
    }
}
