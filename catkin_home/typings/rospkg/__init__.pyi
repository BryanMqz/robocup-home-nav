"""
This type stub file was generated by pyright.
"""

from .common import MANIFEST_FILE, ResourceNotFound, STACK_FILE
from .environment import get_etc_ros_dir, get_log_dir, get_ros_home, get_ros_package_path, get_ros_paths, get_ros_root, get_test_results_dir, on_ros_path
from .manifest import InvalidManifest, Manifest, parse_manifest_file
from .rospack import RosPack, RosStack, expand_to_packages, get_package_name, get_stack_version_by_dir, list_by_path

"""
Base ROS python library for manipulating ROS packages and stacks.
"""
__version__ = '1.2.8'
