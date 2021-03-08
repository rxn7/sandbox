using System.Diagnostics;
using System.Windows;

namespace Sandbox_Launcher {
    public partial class MainWindow : Window {
        public MainWindow() {
            InitializeComponent();
        }

        private void DownloadButton_Click(object sender, RoutedEventArgs e) {

        }

        private void GithubButton_Click(object sender, RoutedEventArgs e) {
            Process.Start("https://www.github.com/rotthin/sandbox");
        }
    }
}
