Pod::Spec.new do |s|
  s.name             = 'VRHouseFramework'
  s.version          = '0.1.0'
  s.summary          = 'An open-source OpenCV wrapper written in Objective-C'
  s.homepage         = 'https://github.com/netguru/3d-house-framework'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'Piotr Sochalewski' => 'piotr.sochalewski@netguru.co' }
  s.source           = { :git => 'https://github.com/netguru/3d-house-framework.git', :tag => s.version.to_s }

  s.ios.deployment_target = '9.0'

  s.source_files = 'VRHouseFramework/Classes/**/*'
  s.dependency 'OpenCV'
end
