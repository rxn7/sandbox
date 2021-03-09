using System;
using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.IO.Compression;
using System.Net;
using System.Windows;

namespace Sandbox_Launcher {
    enum LauncherStatus {
        READY,
        FAILED,
        DOWNLOADING_GAME,
        DOWNLOADING_UPDATE,
    }

    public partial class MainWindow : Window {
        private readonly string rootPath, versionFile, gameZip, gameExe;

        private LauncherStatus status;
        internal LauncherStatus Status {
            get => status;
            set {
                status = value;
                switch (status) {
                    case LauncherStatus.READY:
                        PlayButton.Content = "Play";
                        break;

                    case LauncherStatus.FAILED:
                        PlayButton.Content = "Update failed - Retry";
                        break;

                    case LauncherStatus.DOWNLOADING_GAME:
                        PlayButton.Content = "Downloading Game";
                        break;

                    case LauncherStatus.DOWNLOADING_UPDATE:
                        PlayButton.Content = "Downloading Update";
                        break;
                }
            }
        }

        public MainWindow() {
            InitializeComponent();
            rootPath = Directory.GetCurrentDirectory();
            versionFile = Path.Combine(rootPath, "ver.txt");
            gameZip = Path.Combine(rootPath, "Sandbox.zip");
            gameExe = Path.Combine(rootPath, "Sandbox", "Sandbox.exe");
        }

        private void CheckForUpdates() {
            if (File.Exists(versionFile)) {
                Version localVer = new Version(File.ReadAllText(versionFile));
                VersionLabel.Content = $"v" + localVer;

                try {
                    WebClient client = new WebClient();
                    Version onlineVer = new Version(client.DownloadString("https://drive.google.com/uc?export=download&id=1EgrEKiUYEtEGBYGDVpFJ9uVGnOOgphj4"));

                    if (onlineVer.IsDifferent(localVer)) InstallGameFiles(true, onlineVer);
                    else Status = LauncherStatus.READY;

                    client.Dispose();
                } catch (Exception ex){
                    Status = LauncherStatus.FAILED;
                    MessageBox.Show($"Error checking for game updates: {ex}");
                }
            } else {
                InstallGameFiles(false, Version.zero);
            }
        }

        private void InstallGameFiles(bool update, Version ver) {
            try {
                WebClient client = new WebClient();

                if (update) {
                    Status = LauncherStatus.DOWNLOADING_UPDATE;
                } else {
                    Status = LauncherStatus.DOWNLOADING_GAME;
                    ver = new Version(client.DownloadString("https://drive.google.com/uc?export=download&id=1EgrEKiUYEtEGBYGDVpFJ9uVGnOOgphj4"));
                }

                client.DownloadFileCompleted += new AsyncCompletedEventHandler(DownloadGameCompletedCallback);
                client.DownloadFileAsync(new Uri("https://drive.google.com/uc?export=download&id=1gSDqmuigCa2KyNjvGnPRuY5Mo6Yan3Yp"), gameZip, ver);
                client.Dispose();
            } catch (Exception ex){
                Status = LauncherStatus.FAILED;
                MessageBox.Show($"Error updating the game files: {ex}");
            }
        }

        private void PlayButton_Click(object sender, RoutedEventArgs e) {
            if (File.Exists(gameExe) && Status == LauncherStatus.READY) {
                ProcessStartInfo startInfo = new ProcessStartInfo(gameExe) {
                    WorkingDirectory = Path.Combine(rootPath, "Sandbox")
                };
                Process.Start(startInfo);

                Close();
            }else if(Status == LauncherStatus.FAILED) {
                CheckForUpdates();
            }
        }

        private void DownloadGameCompletedCallback(object sender, AsyncCompletedEventArgs e) {
            try {
                if (Directory.Exists(Path.Combine(rootPath, "Sandbox"))) {
                    Directory.Delete(Path.Combine(rootPath, "Sandbox"), true);
                }

                string onlineVer = ((Version)e.UserState).ToString();
                ZipFile.ExtractToDirectory(gameZip, rootPath);
                File.Delete(gameZip);

                File.WriteAllText(versionFile, onlineVer);

                VersionLabel.Content = $"v" + onlineVer;
                Status = LauncherStatus.READY;
            }catch(Exception ex) {
                Status = LauncherStatus.FAILED;
                MessageBox.Show($"Error finishing download: {ex}");
            }
        }

        private void GithubButton_Click(object sender, RoutedEventArgs e) {
            Process.Start("https://www.github.com/rotthin/sandbox");
        }

        private void Window_ContentRendered(object sender, EventArgs e) {
            CheckForUpdates();
        }
    }

    struct Version {
        internal static Version zero = new Version(0, 0, 0);

        private readonly short major, minor, subMinor;

        internal Version(short major, short minor, short subMinor) {
            this.major = major;
            this.minor = minor;
            this.subMinor = subMinor;
        }

        internal Version(string version) {
            string[] verStrings = version.Split('.');
            if(verStrings.Length != 3) {
                major = 0;
                minor = 0;
                subMinor = 0;
                return;
            }

            major = short.Parse(verStrings[0]);
            minor = short.Parse(verStrings[1]);
            subMinor = short.Parse(verStrings[2]);
        }

        internal bool IsDifferent(Version other) {
            if(major != other.major) return true;
            if (minor != other.minor) return true;
            if (subMinor != other.subMinor) return true;

            return false;
        }

        public override string ToString() => $"{major}.{minor}.{subMinor}";
    }
}
