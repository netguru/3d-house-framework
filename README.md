# VRHouseFramework

## Requirements

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

TBD

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

TBD

## Author

Piotr Sochalewski, piotr.sochalewski@netguru.co

## License

VRHouseFramework is available under the MIT license. See the LICENSE file for more info.
