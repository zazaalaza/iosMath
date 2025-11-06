# Needed due to
# http://stackoverflow.com/questions/33395675/cocoapods-file-reference-is-a-member-of-multiple-groups
workspace 'iosMath.xcworkspace'

install! 'cocoapods', :deterministic_uuids => false

target 'iosMathExample' do
  project 'iosMath.xcodeproj'
  platform :ios, '17.0'
  pod 'iosMath', :path => './'
end

target 'iosMathTests' do
  project 'iosMath.xcodeproj'
  platform :ios, '17.0'
  pod 'iosMath', :path => './'
end

target 'MacOSMath' do
  project 'MacOSMath.xcodeproj'
  platform :osx, '14.0'
  pod 'iosMath', :path => './'
end
