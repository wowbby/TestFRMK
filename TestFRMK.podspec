
Pod::Spec.new do |s|
  s.name             = 'TestFRMK'
  s.version          = '0.9.0'
  s.summary          = 'description of TestFRMK.'

  s.description      = <<-DESC
Add long description of the pod here.
                       DESC

  s.homepage         = 'https://github.com/wowbby/TestFRMK'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'wowbby' => 'zhengzx@haierubic.com' }
  s.source           = { :git => 'https://github.com/wowbby/TestFRMK.git', :tag => s.version.to_s }


  s.ios.deployment_target = '8.0'

  s.source_files = 'TestFRMK/Classes/**/*'
  s.vendored_frameworks = 'TestFRMK/FRMKS/*.framework'
  s.resources = ['TestFRMK/FRMKS/uSDK.framework/configFiles.bundle']
  s.user_target_xcconfig = { 'OTHER_LDFLAGS' => '-lc++' }
  s.frameworks = 'Foundation'
end
