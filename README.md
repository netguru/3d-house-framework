# VRHouseFramework

## Requirements

* AndroidStudio

### iOS

* Xcode
* CocoaPods

## Installation

### iOS

VRHouseFramework is available through [CocoaPods](https://cocoapods.org). To install
it, simply add the following line to your Podfile:

```ruby
pod 'VRHouseFramework', :git => 'git@github.com:netguru/3d-house-framework.git', :inhibit_warnings => true
```

### Android

1. Open AndroidStudio project (I assume it has Git configured).
2. From android studio project terminal add this repository as submodule 
```bash
git submodule add git@github.com:netguru/3d-house-framework.git
```

3. You will get message like "Unregistered VCS root detected ..."
Click on "Add root".
Now you can see multiple git repositories at the right bottom of the android studio.

4. Goto file menu —> project structure
5. Click ‘+’ on left top to add module
6. Select ‘Import Gradle Project’ from new window
7. Select the sub-module folder
8. Give the actual sub-module project name (if needed)
9. Sync 
10. You should have your sub-module added!
11. Now just in you app level build.gradle add dependency 
```
implementation project(':vrhouseframework')
```
and thats all!


## Development

### iOS

#### Tools

* Xcode 10.1 with latest iOS SDK (12.1)
* [Carthage](https://github.com/Carthage/Carthage) 0.31.2 or higher
* [CocoaPods](https://github.com/CocoaPods/CocoaPods) 1.5.3 or higher

#### Installation

1. Clone repository:

```bash
# over https:
git clone https://github.com/netguru/3d-house-framework.git
# or over SSH:
git clone git@github.com:netguru/3d-house-framework.git
```

2. Run Carthage:

```bash
carthage bootstrap --platform iOS --cache-builds
```

3. Run CocoaPods:

```bash
pod install
```

4. Open `VRHouseFramework.xcworkspace` file and build the project.

#### Linting

Run `pod lib lint --allow-warnings` to lint the library against CocoaPods.

### Android

Just clone the repo and open it in AndroidStudio.
Under "app" is sample app that checks if library module works.
Library itself is in "vrhouseframework" module (and it's relying on "opencv" submodule).

## Author

Piotr Sochalewski, piotr.sochalewski@netguru.co

## License

VRHouseFramework is available under the MIT license. See the LICENSE file for more info.
