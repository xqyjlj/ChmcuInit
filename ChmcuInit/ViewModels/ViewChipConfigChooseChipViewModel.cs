using ChmcuInit.Models;
using ChmcuInit.Service;
using ChmcuInit.Views;
using Prism.Commands;
using Prism.Mvvm;
using Prism.Regions;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace ChmcuInit.ViewModels
{
    public class ViewChipConfigChooseChipViewModel : BindableBase, INotifyPropertyChanged
    {
        private readonly List<string> AllCompanyName = new List<string>();
        private readonly List<string> AllFamilyName = new List<string>();
        private readonly List<string> AllSubFamilyName = new List<string>();
        private readonly List<string> AllMcuName = new List<string>();
        private readonly List<ChipItemsModel> AllMcuModel = new List<ChipItemsModel>();

        public ViewChipConfigChooseChipViewModel(IRegionManager regionManger)
        {
            this.LoadXmlData();

            #region 加载下拉框
            this.LoadComboBoxChipItems();
            #endregion

            #region 隐藏DataGrid
            CompanyNameDataGridVisibility = Visibility.Collapsed;
            FamilyNameDataGridVisibility = Visibility.Collapsed;
            SubFamilyNameDataGridVisibility = Visibility.Collapsed;
            CoreNameDataGridVisibility = Visibility.Collapsed;
            #endregion

            #region 绑定按钮
            厂家Command = new DelegateCommand(厂家Click);
            家族Command = new DelegateCommand(家族Click);
            组Command = new DelegateCommand(组Click);
            内核Command = new DelegateCommand(内核Click);
            #endregion

            this.LoadDataGridItems();

            regionManger.RegisterViewWithRegion("ViewChipConfigChooseChipFeatureContentRegion", typeof(ViewChipConfigChooseChipFeatures));
        }

        #region 加载Xml数据
        private void LoadXmlData()
        {
            XMLFamilies xMLFamilies = new XMLFamilies();
            var companyNames = xMLFamilies.GetAllCompanyName();
            foreach (var companyName in companyNames)
            {
                AllCompanyName.Add(companyName);
                var familyNames = xMLFamilies.GetAllFamilyName(companyName);
                foreach (var familyName in familyNames)
                {
                    AllFamilyName.Add(familyName);
                    var subFamilyNames = xMLFamilies.GetAllSubFamilyName(companyName, familyName);
                    foreach (var subFamilyName in subFamilyNames)
                    {
                        AllSubFamilyName.Add(subFamilyName);
                        var mcuNames = xMLFamilies.GetAllMcuName(companyName, familyName, subFamilyName);
                        {
                            foreach (var mcuName in mcuNames)
                            {
                                AllMcuName.Add(mcuName);
                                ChipItemsModel chipItemsSourceModel = new ChipItemsModel();
                                var mcuFeatures = xMLFamilies.GetAllMcuFeatures(companyName, familyName, subFamilyName, mcuName);

                                chipItemsSourceModel.companyName = companyName;
                                chipItemsSourceModel.familyName = familyName;
                                chipItemsSourceModel.subFamilyName = subFamilyName;
                                chipItemsSourceModel.mcuName = mcuName;
                                chipItemsSourceModel.mcuFeature = mcuFeatures;
                                AllMcuModel.Add(chipItemsSourceModel);
                            }
                        }
                    }
                }
            }
        }
        #endregion

        #region DataGrid可见性
        private System.Windows.Visibility companyNameDataGridVisibility;

        public System.Windows.Visibility CompanyNameDataGridVisibility
        {
            get { return companyNameDataGridVisibility; }
            set
            {
                companyNameDataGridVisibility = value;
                this.RaisePropertyChanged("CompanyNameDataGridVisibility");
            }
        }

        private System.Windows.Visibility familyNameDataGridVisibility;

        public System.Windows.Visibility FamilyNameDataGridVisibility
        {
            get { return familyNameDataGridVisibility; }
            set
            {
                familyNameDataGridVisibility = value;
                this.RaisePropertyChanged("FamilyNameDataGridVisibility");
            }
        }

        private System.Windows.Visibility subFamilyNameDataGridVisibility;

        public System.Windows.Visibility SubFamilyNameDataGridVisibility
        {
            get { return subFamilyNameDataGridVisibility; }
            set
            {
                subFamilyNameDataGridVisibility = value;
                this.RaisePropertyChanged("SubFamilyNameDataGridVisibility");
            }
        }

        private System.Windows.Visibility coreNameDataGridVisibility;

        public System.Windows.Visibility CoreNameDataGridVisibility
        {
            get { return coreNameDataGridVisibility; }
            set
            {
                coreNameDataGridVisibility = value;
                this.RaisePropertyChanged("CoreNameDataGridVisibility");
            }
        }
        #endregion

        #region 下拉框
        private List<ChipItemsModel> chipComboBoxItemsSource;

        public List<ChipItemsModel> ChipComboBoxItemsSource
        {
            get { return chipComboBoxItemsSource; }
            set
            {
                chipComboBoxItemsSource = value;
                this.RaisePropertyChanged("ChipComboBoxSelectedItem");
            }
        }

        private void LoadComboBoxChipItems()
        {
            this.ChipComboBoxItemsSource = new List<ChipItemsModel>();
            foreach (var item in AllMcuModel)
            {
                ChipItemsModel chipItemsSourceModel = new ChipItemsModel();
                chipItemsSourceModel.companyName = item.companyName;
                chipItemsSourceModel.familyName = item.familyName;
                chipItemsSourceModel.subFamilyName = item.subFamilyName;
                chipItemsSourceModel.mcuName = item.mcuName;
                chipItemsSourceModel.mcuFeature = item.mcuFeature;
                ChipComboBoxItemsSource.Add(chipItemsSourceModel);
            }
        }
        #endregion  

        #region 绑定按钮
        public DelegateCommand 厂家Command { get; private set; }

        private void 厂家Click()
        {
            if (CompanyNameDataGridVisibility == Visibility.Collapsed)
            {
                CompanyNameDataGridVisibility = Visibility.Visible;
            }
            else
            {
                CompanyNameDataGridVisibility = Visibility.Collapsed;
            }
        }

        public DelegateCommand 家族Command { get; private set; }

        private void 家族Click()
        {
            if (FamilyNameDataGridVisibility == Visibility.Collapsed)
            {
                FamilyNameDataGridVisibility = Visibility.Visible;
            }
            else
            {
                FamilyNameDataGridVisibility = Visibility.Collapsed;
            }
        }

        public DelegateCommand 组Command { get; private set; }

        private void 组Click()
        {
            if (SubFamilyNameDataGridVisibility == Visibility.Collapsed)
            {
                SubFamilyNameDataGridVisibility = Visibility.Visible;
            }
            else
            {
                SubFamilyNameDataGridVisibility = Visibility.Collapsed;
            }
        }

        public DelegateCommand 内核Command { get; private set; }

        private void 内核Click()
        {
            if (CoreNameDataGridVisibility == Visibility.Collapsed)
            {
                CoreNameDataGridVisibility = Visibility.Visible;
            }
            else
            {
                CoreNameDataGridVisibility = Visibility.Collapsed;
            }
        }
        #endregion

        #region DataGrid数据
        private List<ViewChipConfigChooseChipSelectableModel> companyNameDataGridItemsSource;

        public List<ViewChipConfigChooseChipSelectableModel> CompanyNameDataGridItemsSource
        {
            get { return companyNameDataGridItemsSource; }
            set
            {
                companyNameDataGridItemsSource = value;
                this.RaisePropertyChanged("CompanyNameDataGridItemsSource");
            }
        }

        private List<ViewChipConfigChooseChipSelectableModel> familyNameDataGridItemsSource;

        public List<ViewChipConfigChooseChipSelectableModel> FamilyNameDataGridItemsSource
        {
            get { return familyNameDataGridItemsSource; }
            set
            {
                familyNameDataGridItemsSource = value;
                this.RaisePropertyChanged("FamilyNameDataGridItemsSource");
            }
        }

        private List<ViewChipConfigChooseChipSelectableModel> subFamilyNameDataGridItemsSource;

        public List<ViewChipConfigChooseChipSelectableModel> SubFamilyNameDataGridItemsSource
        {
            get { return subFamilyNameDataGridItemsSource; }
            set
            {
                subFamilyNameDataGridItemsSource = value;
                this.RaisePropertyChanged("SubFamilyNameDataGridItemsSource");
            }
        }

        private List<ViewChipConfigChooseChipDataModel> mcuDataGridItemsSource;

        public List<ViewChipConfigChooseChipDataModel> McuDataGridItemsSource
        {
            get { return mcuDataGridItemsSource; }
            set
            {
                mcuDataGridItemsSource = value;
                this.RaisePropertyChanged("McuDataGridItemsSource");
            }
        }

        private void LoadDataGridItems()
        {
            this.CompanyNameDataGridItemsSource = new List<ViewChipConfigChooseChipSelectableModel>();
            this.FamilyNameDataGridItemsSource = new List<ViewChipConfigChooseChipSelectableModel>();
            this.SubFamilyNameDataGridItemsSource = new List<ViewChipConfigChooseChipSelectableModel>();
            this.McuDataGridItemsSource = new List<ViewChipConfigChooseChipDataModel>();
            foreach (var companyName in AllCompanyName)
            {
                ViewChipConfigChooseChipSelectableModel item = new ViewChipConfigChooseChipSelectableModel();
                item.是否选中 = false;
                item.名字 = companyName;
                CompanyNameDataGridItemsSource.Add(item);
            }
            foreach (var familyName in AllFamilyName)
            {
                ViewChipConfigChooseChipSelectableModel item = new ViewChipConfigChooseChipSelectableModel();
                item.是否选中 = false;
                item.名字 = familyName;
                FamilyNameDataGridItemsSource.Add(item);
            }
            foreach (var subFamilyName in AllSubFamilyName)
            {
                ViewChipConfigChooseChipSelectableModel item = new ViewChipConfigChooseChipSelectableModel();
                item.是否选中 = false;
                item.名字 = subFamilyName;
                SubFamilyNameDataGridItemsSource.Add(item);
            }

            foreach (var allMcuModel in AllMcuModel)
            {
                ViewChipConfigChooseChipDataModel item = new ViewChipConfigChooseChipDataModel();
                item.价格每千片 = "9999";
                item.状态 = @"预售";
                item.型号 = allMcuModel.mcuName;
                item.封装 = allMcuModel.mcuFeature.McuPackageName;
                item.Flash = allMcuModel.mcuFeature.Flash;
                item.Ram = allMcuModel.mcuFeature.Ram;
                item.IO = allMcuModel.mcuFeature.IO;
                item.频率 = allMcuModel.mcuFeature.Frequency;
                McuDataGridItemsSource.Add(item);
            }
        }
        #endregion

        public DelegateCommand<object> _myAgeCommand { get; private set; }
        public DelegateCommand<object> MyAgeCommand
        {
            get
            {
                if (_myAgeCommand == null)
                    _myAgeCommand = new DelegateCommand<object>(MySelectedCell);
                return _myAgeCommand;
            }
        }



        private void MySelectedCell(object obj)
        {
            Console.WriteLine("1111111");
            // Rest of the code
        }
    }
}
